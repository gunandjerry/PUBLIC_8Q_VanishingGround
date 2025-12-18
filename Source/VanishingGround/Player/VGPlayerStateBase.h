// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "VGPlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class VANISHINGGROUND_API AVGPlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAbilitySystemComponent> ASC;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UVGCharacterData> PlayerData;
public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override { return ASC;  }

protected:
	UPROPERTY()
	TObjectPtr<class UVGAttributeSet_Health> HealthAttributeSet;
	UPROPERTY()
	TObjectPtr<class UVGAttributeSet_Character> CharacterAttributeSet;
public:
	TObjectPtr<class UVGAttributeSet_Health> GetHealthAttributeSet() const { return HealthAttributeSet; }
	TObjectPtr<class UVGAttributeSet_Character> GetCharacterAttributeSet() const { return CharacterAttributeSet; }

public:
	AVGPlayerStateBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// 임시 - GI에 저장된 스탯값 덮어쓰기
	void InitPlayerStats();
};
