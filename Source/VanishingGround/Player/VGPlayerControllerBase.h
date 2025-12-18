// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VGPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class VANISHINGGROUND_API AVGPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UVGPlayerInputData> InputData;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACharacter> AvatarActorClass;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class ACharacter> AvatarActor;


public:
	AVGPlayerControllerBase();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;


public:
	void SpawnAvatarActor(FVector Location, FRotator Rotation);


public:
	void Confirm();
	void Cancel();
};
