// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "VGMonsterCharacterBase.generated.h"

UCLASS()
class VANISHINGGROUND_API AVGMonsterCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UVGAttributeSet_Health> HealthAttributeSet;
	UPROPERTY()
	TObjectPtr<class UVGAttributeSet_Character> CharacterAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UVGCharacterData> MonsterData;

public:
	AVGMonsterCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return ASC; }
};
