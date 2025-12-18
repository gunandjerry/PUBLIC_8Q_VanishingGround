// Copyright (c) 2025, VanishingGround. All rights reserved.


#include "GAS/VGAttributeSet_Character.h"

void UVGAttributeSet_Character::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
}

void UVGAttributeSet_Character::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
}

void UVGAttributeSet_Character::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
