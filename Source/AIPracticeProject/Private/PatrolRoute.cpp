// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"
#include "Components/SplineComponent.h"

// Sets default values
APatrolRoute::APatrolRoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent.Get());

	Direction = 1;
	PatrolIndex = 0;
}

void APatrolRoute::IncrementPatrolRoute()
{
	// Direction will be either 1 or -1
	const int32 PatrolPointsNum = SplineComponent->GetNumberOfSplinePoints();
	
	PatrolIndex += Direction;
	if(PatrolIndex == (PatrolPointsNum - 1))
	{
		Direction = -1;
	}
	else if(PatrolIndex == 0)
	{
		Direction  = 1;
	}
}

FVector APatrolRoute::GetSplinePointAsWorldPosition() const
{
	return SplineComponent->GetWorldLocationAtSplinePoint(PatrolIndex);
}


