// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_HasPatrolRoute.h"

#include "AIController.h"
#include "EnemyAI.h"
#include "PatrolRoute.h"

UBTD_HasPatrolRoute::UBTD_HasPatrolRoute()
{
	NodeName = "Has Patrol Route";
}

bool UBTD_HasPatrolRoute::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	IEnemyAI* EnemyAIInterface {Cast<IEnemyAI>(OwnerComp.GetAIOwner()->GetPawn())};
	return IsValid(EnemyAIInterface->GetPatrolRoute());
}

FString UBTD_HasPatrolRoute::GetStaticDescription() const
{
	return FString("Checks if the AI has a patrol route");
}
