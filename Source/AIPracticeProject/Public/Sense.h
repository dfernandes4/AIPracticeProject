// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "Sense.generated.h"

/**
 * 
 */
UENUM()
enum class ESense : uint8
{
	None,
	Seeing,
	Hearing,
	Damaging
};

UCLASS()
class AIPRACTICEPROJECT_API USense : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};
