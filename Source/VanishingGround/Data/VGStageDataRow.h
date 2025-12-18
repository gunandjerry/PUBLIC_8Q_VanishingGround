// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "VGStageDataRow.generated.h"

USTRUCT(BlueprintType)
struct FMonsterSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AVGMonsterCharacterBase> MonsterClass;

	// 임시, 스폰포인트 액터를 사용하는게 나을 듯.
	UPROPERTY(EditDefaultsOnly)
	FTransform SpawnTransform;
};



USTRUCT(BlueprintType)
struct FVGStageDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FMonsterSpawnInfo> Monsters;

	// Obsolete
	UPROPERTY(EditDefaultsOnly)
	FTransform PlayerSpawnTransform;
};