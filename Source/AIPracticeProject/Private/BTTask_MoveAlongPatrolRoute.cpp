// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveAlongPatrolRoute.h"

#include "AIController.h"
#include "EnemyAI.h"
#include "EnemyBase.h"
#include "PatrolRoute.h"
#include "Navigation/PathFollowingComponent.h"



EBTNodeResult::Type UBTTask_MoveAlongPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IEnemyAI* EnemyAIInterface = Cast<IEnemyAI>(OwnerComp.GetAIOwner()->GetPawn());
	
	if(EnemyAIInterface != nullptr)
	{
		const TObjectPtr<APatrolRoute> PatrolRoute {EnemyAIInterface->GetPatrolRoute()};
		const FVector PointPosition {PatrolRoute->GetSplinePointAsWorldPosition()};
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalLocation(PointPosition);
		MoveRequest.SetAcceptanceRadius(10.f);
		
		const FPathFollowingRequestResult MoveResult {(OwnerComp.GetAIOwner()->MoveTo(MoveRequest))};
		PatrolRoute->IncrementPatrolRoute();
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_MoveAlongPatrolRoute::GetStaticDescription() const
{
	return FString("Moves along the patrol route");
}

EBTNodeResult::Type UBTTask_MoveAlongPatrolRoute::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->StopMovement();
	return EBTNodeResult::Succeeded;
}

