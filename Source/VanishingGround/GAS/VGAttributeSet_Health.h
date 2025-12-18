// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAS/VGAttributeSetHelper.h"
#include "VGAttributeSet_Health.generated.h"


/**
 * [범용] 체력, 현재체력 정의
 */

UCLASS()
class VANISHINGGROUND_API UVGAttributeSet_Health : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UVGAttributeSet_Health, Health)

	UPROPERTY()
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UVGAttributeSet_Health, MaxHealth)

public:
	UPROPERTY(EditDefaultsOnly, Category = GAS)
	uint8 bHealOnMaxHpIncreased : 1{ true };

public:
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
