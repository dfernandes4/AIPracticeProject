// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "MovementSpeed.generated.h"

/**
 * 
 */
UENUM()
enum class EMovementSpeed : uint8
{
	Idle,
	Walk,
	Run,
	Sprint
};
