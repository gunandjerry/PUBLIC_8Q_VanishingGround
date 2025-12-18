// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VGPlayerInputData.generated.h"

/**
 * 
 */
UCLASS()
class VANISHINGGROUND_API UVGPlayerInputData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* Input_Confirm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* Input_Cancel;
};
