// Copyright (c) 2025, VanishingGround. All rights reserved.


#include "GAS/Abilities/VGTurnAbilityBase.h"
#include "Battle/VGBattleSubsystem.h"
#include "GAS/VGGameplayTags.h"
#include "Battle/VGBattleInstance.h"

UVGTurnAbilityBase::UVGTurnAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;

	FAbilityTriggerData data;
	data.TriggerTag = GET_GAMEPLAY_TAG("Ability.TurnAbility");
	data.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(data);
}

void UVGTurnAbilityBase::FinishTurnAbility(bool bWasCancelled)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bWasCancelled, bWasCancelled);

	if (!CurrentActorInfo) return;
	AActor* Avatar = CurrentActorInfo->AvatarActor.Get();
	ensure(Avatar);
	
	UVGBattleSubsystem* BattleSystem = GetWorld()->GetSubsystem<UVGBattleSubsystem>();
	ensure(BattleSystem);

	BattleSystem->NotifyTurnAbilityFinished(Avatar);
}