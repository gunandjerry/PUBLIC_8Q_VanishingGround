// Copyright (c) 2025, VanishingGround. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"

#define GET_GAMEPLAY_TAG(TagName) FGameplayTag::RequestGameplayTag(FName(TEXT(TagName)))
