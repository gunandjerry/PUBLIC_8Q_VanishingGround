// Copyright (c) 2025, VanishingGround. All rights reserved.


#include "Player/Character/VGHeroCharacterBase.h"
#include "Player/VGPlayerStateBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

AVGHeroCharacterBase::AVGHeroCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AVGHeroCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVGHeroCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Cast<IAbilitySystemInterface>(GetPlayerState())->GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
}

void AVGHeroCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* AVGHeroCharacterBase::GetAbilitySystemComponent() const
{
	return GetPlayerState<AVGPlayerStateBase>()->GetAbilitySystemComponent();
}

