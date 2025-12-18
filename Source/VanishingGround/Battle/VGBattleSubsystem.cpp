// Copyright (c) 2025, VanishingGround. All rights reserved.


#include "Battle/VGBattleSubsystem.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GAS/VGGameplayTags.h"
#include "Battle/VGBattleInstance.h"
#include "Core/VGGameInstance.h"
#include "Data/VGStageDataRow.h"

void UVGBattleSubsystem::StartBattle()
{
	UVGGameInstance* GameInstance = GetWorld()->GetGameInstance<UVGGameInstance>();
	ensure(GameInstance);

	BattleInstance = NewObject<UVGBattleInstance>(this);
	BattleInstance->Init(GameInstance, this);
	BattleInstance->Start(GameInstance->SelectedStageID);
}

void UVGBattleSubsystem::EndBattle(EVGBattleResult Result)
{
	// 게임모드 거쳐서 UI 띄우는게 나을 듯.
	OnBattleFinished.Broadcast(Result);

	BattleInstance->bBattleFinished = true;
}

void UVGBattleSubsystem::NotifyTurnAbilityFinished(AActor* ActingActor)
{
	ensure(BattleInstance);
	
	BattleInstance->NotifyActionFinished(ActingActor);
}