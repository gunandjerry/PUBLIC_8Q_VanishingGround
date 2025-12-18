// Copyright (c) 2025, VanishingGround. All rights reserved.


#include "Player/VGPlayerStateBase.h"
#include "GAS/VGAttributeSet_Health.h"
#include "GAS/VGAttributeSet_Character.h"
#include "GAS/VGCharacterData.h"
#include "Core/VGGameInstance.h"

AVGPlayerStateBase::AVGPlayerStateBase()
{
	HealthAttributeSet = CreateDefaultSubobject<UVGAttributeSet_Health>(TEXT("HealthAttributeSet"));
	CharacterAttributeSet = CreateDefaultSubobject<UVGAttributeSet_Character>(TEXT("CharacterAttributeSet"));
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
}

void AVGPlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	ensure(PlayerData != nullptr);

	HealthAttributeSet->SetMaxHealth(PlayerData->Health);
	HealthAttributeSet->SetHealth(PlayerData->Health);
	CharacterAttributeSet->SetAttackPoint(PlayerData->AttackPoint);
	CharacterAttributeSet->SetDefensePoint(PlayerData->DefensePoint);
	CharacterAttributeSet->SetSpeed(PlayerData->Speed);
	CharacterAttributeSet->SetCriticalChance(PlayerData->CriticalChance);
	CharacterAttributeSet->SetCriticalMultiplier(PlayerData->CriticalMultiplier);
	CharacterAttributeSet->SetAccuracy(PlayerData->Accuracy);
	CharacterAttributeSet->SetEvasion(PlayerData->Evasion);

	for (const auto& ability : PlayerData->InitialAbilities)
	{
		if (ability)
		{
			FGameplayAbilitySpec spec(ability.Get(), 1);
			ASC->GiveAbility(spec);
		}
	}

	for (const auto& effect : PlayerData->InitialEffects)
	{
		FGameplayEffectSpecHandle spec = ASC->MakeOutgoingSpec(effect.Get(), 1, ASC->MakeEffectContext());
		ASC->ApplyGameplayEffectSpecToSelf(*spec.Data.Get());
	}
}

void AVGPlayerStateBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AVGPlayerStateBase::InitPlayerStats()
{
	UVGGameInstance* GI = GetWorld()->GetGameInstance<UVGGameInstance>();
	ensure(GI);

	HealthAttributeSet->SetMaxHealth(GI->PlayerBaseStats.MaxHealth);
	HealthAttributeSet->SetHealth(GI->PlayerBaseStats.MaxHealth);
	CharacterAttributeSet->SetAttackPoint(GI->PlayerBaseStats.AttackPoint);
	CharacterAttributeSet->SetDefensePoint(GI->PlayerBaseStats.DefensePoint);
	CharacterAttributeSet->SetSpeed(GI->PlayerBaseStats.Speed);
	CharacterAttributeSet->SetCriticalChance(GI->PlayerBaseStats.CriticalChance);
	CharacterAttributeSet->SetCriticalMultiplier(GI->PlayerBaseStats.CriticalMultiplier);
	CharacterAttributeSet->SetAccuracy(GI->PlayerBaseStats.Accuracy);
	CharacterAttributeSet->SetEvasion(GI->PlayerBaseStats.Evasion);
}
