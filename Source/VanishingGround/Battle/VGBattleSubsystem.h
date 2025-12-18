// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "VGBattleSubsystem.generated.h"

UENUM(BlueprintType)
enum class EVGBattleResult : uint8
{
	None,
	Victory,
	Defeat
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBattleFinished, EVGBattleResult, Result);

UCLASS()
class VANISHINGGROUND_API UVGBattleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


private:
	UPROPERTY()
	TObjectPtr<class UVGBattleInstance> BattleInstance{ nullptr };

public:
	UPROPERTY(BlueprintAssignable)
	FOnBattleFinished OnBattleFinished;

	/*UFUNCTION(BlueprintCallable, Category = "Battle")
	class UVGBattleInstance* GetBattleInstance() const { return BattleInstance; }*/

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void StartBattle();

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void EndBattle(EVGBattleResult Result);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void NotifyTurnAbilityFinished(AActor* ActingActor);
};