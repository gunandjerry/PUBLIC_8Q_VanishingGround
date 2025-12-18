// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VGCharacterData.generated.h"

/**
 * 
 */
UCLASS()
class VANISHINGGROUND_API UVGCharacterData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	float Health = 100.0f;
	UPROPERTY(EditDefaultsOnly)
	float AttackPoint = 10.0f;
	UPROPERTY(EditDefaultsOnly)
	float DefensePoint = 0.0f;
	UPROPERTY(EditDefaultsOnly)
	float Speed = 10.0f;
	UPROPERTY(EditDefaultsOnly)
	float CriticalChance = 0.0f;
	UPROPERTY(EditDefaultsOnly)
	float CriticalMultiplier = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	float Accuracy = 1.0f;
	UPROPERTY(EditDefaultsOnly)
	float Evasion = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> InitialAbilities;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GAS)
	TArray<TSubclassOf<class UGameplayEffect>> InitialEffects;
};
