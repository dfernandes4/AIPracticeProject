// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyAI.generated.h"

enum class EMovementSpeed : uint8;

class APatrolRoute;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyAI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AIPRACTICEPROJECT_API IEnemyAI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "Interface Functions")
	virtual APatrolRoute* GetPatrolRoute() = 0;
	UFUNCTION(Category = "Interface Functions")
	virtual float SetMovementSpeed(const EMovementSpeed Speed) = 0;
};
