// Copyright (c) 2025, VanishingGround. All rights reserved.


#include "GAS/VGAttributeSet_Health.h"

void UVGAttributeSet_Health::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	/*if (Attribute == GetHealthAttribute())
	{
		if (GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(GET_GAMEPLAY_TAG_PLAYER_STATE_ISIMMORTAL))
		{
			float OldHealth = GetHealth();
			NewValue = OldHealth > NewValue ? OldHealth : NewValue;
		}
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
	}*/
}

void UVGAttributeSet_Health::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		if (bHealOnMaxHpIncreased)
		{
			float gap = NewValue - OldValue;
			if (gap > 0.0f)
			{
				SetHealth(GetHealth() + gap);
			}
		}

		if (GetHealth() > NewValue)
		{
			SetHealth(NewValue);
		}
	}
}

void UVGAttributeSet_Health::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

}
