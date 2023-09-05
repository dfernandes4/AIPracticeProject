// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "AIState.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Passive,
	Attacking,
	Frozen,
	Investigating,
	Dead
};

/**
 * 
 */
UCLASS(BlueprintType)
class AIPRACTICEPROJECT_API UAIState : public UUserDefinedEnum
{
	GENERATED_BODY()

	UAIState();
};
