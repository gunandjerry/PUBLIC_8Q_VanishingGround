// Copyright (c) 2025, VanishingGround. All rights reserved.


#include "Battle/VGBattleInstance.h"
#include "GAS/VGGameplayTags.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Data/VGStageDataRow.h"
#include "Core/VGGameInstance.h"
#include "GameFramework\Character.h"
#include "Battle/VGBattleSubsystem.h"
#include "Monster/VGMonsterCharacterBase.h"
#include "Player/VGPlayerStateBase.h"

#include "GAS/VGAttributeSet_Health.h"
#include "GAS/VGAttributeSet_Character.h"

void UVGBattleInstance::Init(UVGGameInstance* InGI, UVGBattleSubsystem* InOwnerSubsystem, ETurnOrderingType _OrderingType)
{
	GameInstance = InGI;
	BattleSystem = InOwnerSubsystem;
	PlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<AVGPlayerStateBase>();
	TurnIndex = 0;
	Units.Reset();
	OrderingType = _OrderingType;
}

void UVGBattleInstance::Start(FName StageID)
{
	ensure(GameInstance);
	ensure(BattleSystem);
	ensure(PlayerState);

	const FVGStageDataRow* Row = GameInstance->StageData->FindRow<FVGStageDataRow>(StageID, TEXT("Row Names"));
	ensure(Row);

	ConstructBattle(*Row);



	// 여기서 지연이나 이펙트 재생



	UpdateTurnOrder();

	// 첫 턴 시작
	if (TurnOrder.IsEmpty())
	{
		BattleSystem->EndBattle(EVGBattleResult::None);
		return;
	}
	BeginTurn(TurnOrder[0]);
}

void UVGBattleInstance::ConstructBattle(const FVGStageDataRow& Row)
{
	ensure(GameInstance->HeroCharacterClass);

	AActor* Hero = PlayerState->GetPawn();

	// 플레이어 스탯 초기화 (임시)
	PlayerState->InitPlayerStats();

	int32 CurUnitIdx = 0;
	Units.Add(FVGBattleUnit{});
	Units[CurUnitIdx].Actor = Hero;
	Units[CurUnitIdx].Team = EVGBattleTeam::Player;
	Units[CurUnitIdx].Speed = ReadSpeed(CurUnitIdx);
	Units[CurUnitIdx].bAlive = true;
	Units[CurUnitIdx].OrderPointAcc = Units[CurUnitIdx].Speed;
	Units[CurUnitIdx].TieBreaker = 0;

	BindDeathDetection(CurUnitIdx);


	// 몬스터 스폰
	for (const FMonsterSpawnInfo& E : Row.Monsters)
	{
		if (!E.MonsterClass) continue;

		AActor* Enemy = GetWorld()->SpawnActor<AActor>(E.MonsterClass.Get(), E.SpawnTransform);
		if (!Enemy) continue;

		CurUnitIdx++;
		Units.Add(FVGBattleUnit{});
		Units[CurUnitIdx].Actor = Enemy;
		Units[CurUnitIdx].Team = EVGBattleTeam::Enemy;
		Units[CurUnitIdx].Speed = ReadSpeed(CurUnitIdx);
		Units[CurUnitIdx].bAlive = true;
		Units[CurUnitIdx].OrderPointAcc = Units[CurUnitIdx].Speed;
		Units[CurUnitIdx].TieBreaker = NextTieBreaker++;

		BindDeathDetection(CurUnitIdx);
	}
}

void UVGBattleInstance::UpdateTurnOrder()
{
	// 현재 미지원
	/*switch (OrderingType)
	{
		case ETurnOrderingType::Accumulate:
		{
			break;
		}
		case ETurnOrderingType::OneForOne:
		{
			break;
		}
	}*/

	TurnOrder.Reset();

	// 속도 버프 처리해야 되면 주석 풀기
	/*for (int32 i = 0; i < Units.Num(); ++i)
	{
		Units[i].Speed = ReadSpeed(Units[i].Actor.Get());
	}*/

	// 시뮬레이션용 / 실제 OrderPoint는 행동하기 전까지 갱신 X
	struct FNode
	{
		int32 UnitIdx;
		float OrderPointAcc;
		int32 TieBreaker;
	};

	auto LessCompare = [](const FNode& A, const FNode& B) {
		if (A.OrderPointAcc != B.OrderPointAcc) return A.OrderPointAcc < B.OrderPointAcc;
		return A.TieBreaker < B.TieBreaker;
		};

	TArray<FNode> Heap;
	Heap.Reserve(Units.Num());

	for (int32 i = 0; i < Units.Num(); ++i)
	{
		const FVGBattleUnit& Unit = Units[i];
		if (!Unit.bAlive || !Unit.Actor.IsValid()) continue;
		if (Unit.Speed <= 0.f) continue;

		Heap.Add({ i, Unit.OrderPointAcc, Unit.TieBreaker });
	}

	Heap.Heapify(LessCompare);

	const int32 N = FMath::Max(0, TurnOrderCount);
	for (int32 k = 0; k < N && Heap.Num() > 0; ++k)
	{
		FNode Top;
		Heap.HeapPop(Top, LessCompare);

		if (Units.IsValidIndex(Top.UnitIdx))
		{
			TurnOrder.Add(Top.UnitIdx);
		}

		const float Spd = Units[Top.UnitIdx].Speed;
		Top.OrderPointAcc += Spd;

		Heap.HeapPush(Top, LessCompare);
	}

	// UI 갱신은 여기서 하면 될 듯.
}

void UVGBattleInstance::BindDeathDetection(int32 UnitIdx)
{
	UAbilitySystemComponent* ASC = GetASC(UnitIdx);
	ensure(ASC);

	ASC->GetGameplayAttributeValueChangeDelegate(UVGAttributeSet_Health::GetHealthAttribute())
		.AddLambda([this, UnitIdx](const FOnAttributeChangeData& Data) {
			if (Data.NewValue <= 0.f)
			{
				MarkDead(UnitIdx);
			}
		 });
}

void UVGBattleInstance::BeginTurn(int32 UnitIdx)
{
	ensure(Units.IsValidIndex(UnitIdx));

	++TurnIndex;

	UE_LOG(LogTemp, Log, TEXT("[Battle Turn %d] Begin: %s (OrderPoint: %.0f)"), TurnIndex, *GetNameSafe(Units[UnitIdx].Actor.Get()), Units[UnitIdx].OrderPointAcc);

	const bool bTriggered = TriggerTurnAbility(UnitIdx);
	ensure(bTriggered);

	// 어떤 Ability도 반응하지 않는 경우 분기가 필요할지?
	/*if (!bTriggered)
	{
		NotifyActionFinished(Actor);
	}*/
}

bool UVGBattleInstance::TriggerTurnAbility(int32 UnitIdx)
{
	UAbilitySystemComponent* ASC = GetASC(UnitIdx);
	if (!ASC) return false;

	FGameplayTag TurnAbilityTag = GET_GAMEPLAY_TAG("Ability.TurnAbility");

	FGameplayEventData EventData;
	EventData.EventTag = TurnAbilityTag;
	EventData.Instigator = Units[UnitIdx].Actor.Get();


	// 타겟 지정은 플레이어 GA에서


	int32 TriggeredGANum = ASC->HandleGameplayEvent(TurnAbilityTag, &EventData);
	if (TriggeredGANum > 0) return true;
	return false;
}

void UVGBattleInstance::NotifyActionFinished(AActor* ActingActor)
{
	EndBattleIfNeeded();

	if (bBattleFinished) return;

	// 행동한 유닛의 OrderPoint 누적
	const int32 ActingIdx = FindUnitIndex(ActingActor);
	if (ActingIdx != INDEX_NONE && Units[ActingIdx].bAlive)
	{
		Units[ActingIdx].OrderPointAcc += Units[ActingIdx].Speed;
	}

	UpdateTurnOrder();

	if (TurnOrder.IsEmpty())
	{
		BattleSystem->EndBattle(EVGBattleResult::Defeat);
		return;
	}

	BeginTurn(TurnOrder[0]);
}

int32 UVGBattleInstance::FindUnitIndex(AActor* Actor) const
{
	if (!Actor) return INDEX_NONE;
	for (int32 i = 0; i < Units.Num(); ++i)
	{
		if (Units[i].Actor.Get() == Actor) return i;
	}
	return INDEX_NONE;
}

void UVGBattleInstance::MarkDead(int32 UnitIdx)
{
	if (UnitIdx == INDEX_NONE) return;
	if (!Units[UnitIdx].bAlive) return;

	Units[UnitIdx].bAlive = false;
	UE_LOG(LogTemp, Warning, TEXT("Unit died: %s"), *GetNameSafe(Units[UnitIdx].Actor.Get()));

	UAbilitySystemComponent* ASC = GetASC(UnitIdx);
	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UVGAttributeSet_Health::GetHealthAttribute()).Clear();
	}

	EndBattleIfNeeded();
	
	if (!bBattleFinished)
	{
		UpdateTurnOrder();
	}
}

void UVGBattleInstance::EndBattleIfNeeded()
{
	bool bPlayerAlive = false;
	bool bAnyEnemyAlive = false;

	for (const FVGBattleUnit& U : Units)
	{
		if (!U.bAlive || !U.Actor.IsValid()) continue;

		if (U.Team == EVGBattleTeam::Player) bPlayerAlive = true;
		if (U.Team == EVGBattleTeam::Enemy) bAnyEnemyAlive = true;
	}

	if (!BattleSystem) return;

	if (!bPlayerAlive)
	{
		BattleSystem->EndBattle(EVGBattleResult::Defeat);
	}
	else if (!bAnyEnemyAlive)
	{
		BattleSystem->EndBattle(EVGBattleResult::Victory);
	}
}

float UVGBattleInstance::ReadSpeed(int32 UnitIdx) const
{
	UAbilitySystemComponent* ASC = GetASC(UnitIdx);
	if (!ASC) return 0.0f;
	return ASC->GetNumericAttribute(UVGAttributeSet_Character::GetSpeedAttribute());
}

UAbilitySystemComponent* UVGBattleInstance::GetASC(int32 UnitIdx) const
{
	AActor* Target = Units[UnitIdx].Actor.Get();
	if (!Target) return nullptr;
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Target);
	if (!ASI) return nullptr;
	return ASI->GetAbilitySystemComponent();
}