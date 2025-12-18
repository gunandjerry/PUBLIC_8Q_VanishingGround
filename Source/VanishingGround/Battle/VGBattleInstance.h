// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VGBattleInstance.generated.h"

UENUM(BlueprintType)
enum class EVGBattleTeam : uint8
{
	Player,
	Enemy
};

UENUM(BlueprintType)
enum class ETurnOrderingType : uint8
{
	OneForOne, // 돌아가면서
	Accumulate // 누적
};

USTRUCT()
struct FVGBattleUnit
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<AActor> Actor;
	UPROPERTY()
	EVGBattleTeam Team = EVGBattleTeam::Enemy;
	UPROPERTY()
	float Speed = 0.f;
	UPROPERTY()
	bool bAlive = true;
	UPROPERTY()
	float OrderPointAcc = 0.f; // 이걸 누적해가며 가장 작은 점수를 가진 놈의 순서로 결정
	UPROPERTY()
	int32 TieBreaker = 0; // 누적 포인트가 같을 경우 선후 정하는 용도
};

/**
 * 한 스테이지를 총괄 관리하는 주체
 */
UCLASS()
class VANISHINGGROUND_API UVGBattleInstance : public UObject
{
	GENERATED_BODY()


private:
	UPROPERTY()
	TObjectPtr<class UVGGameInstance> GameInstance{ nullptr };
	UPROPERTY()
	TObjectPtr<class UVGBattleSubsystem> BattleSystem{ nullptr };
	UPROPERTY()
	TObjectPtr<class AVGPlayerStateBase> PlayerState{ nullptr };

	UPROPERTY()
	TArray<FVGBattleUnit> Units;
	UPROPERTY()
	int32 TurnIndex{ 0 };
	
	UPROPERTY()
	TArray<int32> TurnOrder;

public:
	// OneForOne은 현재 지원하지 않음
	UPROPERTY()
	ETurnOrderingType OrderingType{ ETurnOrderingType::Accumulate };
	UPROPERTY()
	int32 NextTieBreaker = 1;
	// 임시. 턴 순서를 8개까지 만들어둠
	UPROPERTY()
	int32 TurnOrderCount = 8;
	UPROPERTY()
	uint8 bBattleFinished : 1{ false };


public:
	void Init(class UVGGameInstance* InGI, class UVGBattleSubsystem* InOwnerSubsystem, ETurnOrderingType OrderingType = ETurnOrderingType::Accumulate);
	void Start(FName StageID);
	void NotifyActionFinished(AActor* ActingActor);
private:
	void ConstructBattle(const struct FVGStageDataRow& Row);
	void UpdateTurnOrder();

	void BindDeathDetection(int32 UnitIdx);
	void BeginTurn(int32 UnitIdx);
	bool TriggerTurnAbility(int32 UnitIdx);

	int32 FindUnitIndex(AActor* Actor) const;
	void MarkDead(int32 UnitIdx);
	void EndBattleIfNeeded();
	float ReadSpeed(int32 UnitIdx) const;
	class UAbilitySystemComponent* GetASC(int32 UnitIdx) const;
};
