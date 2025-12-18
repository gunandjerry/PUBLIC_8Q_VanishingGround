// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "VGTurnAbilityBase.generated.h"

/**
 * 자기 턴에 호출할 GA 베이스
 */
UCLASS()
class VANISHINGGROUND_API UVGTurnAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UVGTurnAbilityBase();
public:
	// 필수 호출
	UFUNCTION(BlueprintCallable)
	void FinishTurnAbility(bool bWasCancelled = false);
};
