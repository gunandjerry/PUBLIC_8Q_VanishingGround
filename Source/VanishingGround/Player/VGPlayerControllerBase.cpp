// Copyright (c) 2025, VanishingGround. All rights reserved.


#include "Player/VGPlayerControllerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/Input/VGPlayerInputData.h"
#include "GameFramework\Character.h"

AVGPlayerControllerBase::AVGPlayerControllerBase()
{
}

void AVGPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
    
    if (ULocalPlayer* LP = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void AVGPlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

    // Dummy pawn
}

void AVGPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
    
    UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
    if (!EIC) return;

    EIC->BindAction(InputData->Input_Confirm, ETriggerEvent::Started, this, &AVGPlayerControllerBase::Confirm);
    EIC->BindAction(InputData->Input_Cancel, ETriggerEvent::Started, this, &AVGPlayerControllerBase::Cancel);
}

void AVGPlayerControllerBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AVGPlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVGPlayerControllerBase::SpawnAvatarActor(FVector Location, FRotator Rotation)
{
    ensure(AvatarActorClass != nullptr);

}

void AVGPlayerControllerBase::Confirm()
{
}

void AVGPlayerControllerBase::Cancel()
{
}
