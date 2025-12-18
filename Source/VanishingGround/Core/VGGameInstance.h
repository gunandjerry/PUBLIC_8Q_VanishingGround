// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VGGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FVGPlayerBaseStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth{ 100.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackPoint{ 10.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefensePoint{ 0.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed{ 1.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalChance{ 0.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalMultiplier{ 1.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Accuracy{ 1.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Evasion{ 0.0f };
};

UCLASS()
class VANISHINGGROUND_API UVGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UDataTable> StageData;
	
	// 선택된 스테이지 ID
	UPROPERTY(BlueprintReadWrite)
	FName SelectedStageID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVGPlayerBaseStats PlayerBaseStats;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACharacter> HeroCharacterClass;
};
