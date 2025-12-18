// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GAS/VGAttributeSetHelper.h"
#include "VGAttributeSet_Character.generated.h"

/**
 * [범용] 기본 스탯 정의
 * AttackPoint - 기본 공격력
 * DefensePoint - 기본 방어력
 * Speed - 턴 스피드 (우선순위)
 * CriticalChance - 치명타 확률
 * CriticalMultiplier - 치명타시 기본 공격력 배수
 * Accuracy - 명중률
 * Evasion - 회피율
 */

UCLASS()
class VANISHINGGROUND_API UVGAttributeSet_Character : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGameplayAttributeData AttackPoint;
	ATTRIBUTE_ACCESSORS(UVGAttributeSet_Character, AttackPoint)

	UPROPERTY()
	FGameplayAttributeData DefensePoint;
	ATTRIBUTE_ACCESSORS(UVGAttributeSet_Character, DefensePoint)

	UPROPERTY()
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UVGAttributeSet_Character, Speed)

	UPROPERTY()
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UVGAttributeSet_Character, CriticalChance)

	UPROPERTY()
	FGameplayAttributeData CriticalMultiplier;
	ATTRIBUTE_ACCESSORS(UVGAttributeSet_Character, CriticalMultiplier)

	UPROPERTY()
	FGameplayAttributeData Accuracy;
	ATTRIBUTE_ACCESSORS(UVGAttributeSet_Character, Accuracy)

	UPROPERTY()
	FGameplayAttributeData Evasion;
	ATTRIBUTE_ACCESSORS(UVGAttributeSet_Character, Evasion)


public:
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
