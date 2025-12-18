// Copyright (c) 2025, VanishingGround. All rights reserved.


#include "Monster/VGMonsterCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GAS/VGAttributeSet_Health.h"
#include "GAS/VGAttributeSet_Character.h"
#include "GAS/VGCharacterData.h"

AVGMonsterCharacterBase::AVGMonsterCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthAttributeSet = CreateDefaultSubobject<UVGAttributeSet_Health>(TEXT("HealthAttributeSet"));
	CharacterAttributeSet = CreateDefaultSubobject<UVGAttributeSet_Character>(TEXT("CharacterAttributeSet"));
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void AVGMonsterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	ensure(MonsterData != nullptr);
	
	HealthAttributeSet->SetMaxHealth(MonsterData->Health);
	HealthAttributeSet->SetHealth(MonsterData->Health);
	CharacterAttributeSet->SetAttackPoint(MonsterData->AttackPoint);
	CharacterAttributeSet->SetDefensePoint(MonsterData->DefensePoint);
	CharacterAttributeSet->SetSpeed(MonsterData->Speed);
	CharacterAttributeSet->SetCriticalChance(MonsterData->CriticalChance);
	CharacterAttributeSet->SetCriticalMultiplier(MonsterData->CriticalMultiplier);
	CharacterAttributeSet->SetAccuracy(MonsterData->Accuracy);
	CharacterAttributeSet->SetEvasion(MonsterData->Evasion);
	
	for (const auto& ability : MonsterData->InitialAbilities)
	{
		if (ability)
		{
			FGameplayAbilitySpec spec(ability.Get(), 1);
			ASC->GiveAbility(spec);
		}
	}

	for (const auto& effect : MonsterData->InitialEffects)
	{
		FGameplayEffectSpecHandle spec = ASC->MakeOutgoingSpec(effect.Get(), 1, ASC->MakeEffectContext());
		ASC->ApplyGameplayEffectSpecToSelf(*spec.Data.Get());
	}
}

void AVGMonsterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

