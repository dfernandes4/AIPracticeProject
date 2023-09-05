 // Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TeleportToRandomLocation.h"

#include "NavigationSystem.h"
#include "Engine/TargetPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

 UBTTask_TeleportToRandomLocation::UBTTask_TeleportToRandomLocation()
 {
 	NodeName = TEXT("Teleport To Random Location");
 }

 EBTNodeResult::Type UBTTask_TeleportToRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
 {
	//Take the Actor and teleport it to a random location
	FNavLocation NavLocation {};
	const TObjectPtr<AAIController> AIController {OwnerComp.GetAIOwner()};
 	const TObjectPtr<ATargetPoint> TargetPoint = Cast<ATargetPoint>(AIController->GetBlackboardComponent()->GetValueAsObject(FName("SpawnTarget")));
 	
	if(IsValid(AIController.Get()))
	{
	  const TObjectPtr<UNavigationSystemV1> NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	  if(IsValid(NavSystem.Get()) && IsValid(TargetPoint.Get()) && NavSystem->GetRandomPointInNavigableRadius(TargetPoint->GetActorLocation(), 500.0f, NavLocation))
	  {
		  if(const TObjectPtr<APawn> Pawn {AIController->GetPawn()})
		  {
			 Pawn->SetActorLocation(NavLocation.Location);
		  }
	  }
	}


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
 }

 FString UBTTask_TeleportToRandomLocation::GetStaticDescription() const
 {
  return FString("Teleports the AI to a random location");
 }
