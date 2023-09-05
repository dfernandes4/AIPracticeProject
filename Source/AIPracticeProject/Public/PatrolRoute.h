// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

class USplineComponent;

UCLASS()
class AIPRACTICEPROJECT_API APatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolRoute();
	UFUNCTION(Category = "PatrolRoute")
	void IncrementPatrolRoute();
	UFUNCTION(Category = "PatrolRoute")
	FVector GetSplinePointAsWorldPosition() const;
private:
	UPROPERTY(VisibleAnywhere, Category = "PatrolRoute", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USplineComponent> SplineComponent;
	UPROPERTY()
	int32 Direction;
	UPROPERTY()
	int32 PatrolIndex;
};
