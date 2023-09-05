// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetPassiveState.h"

#include "EnemyAIController.h"

UBTTask_SetPassiveState::UBTTask_SetPassiveState()
{
	NodeName = "Set State To Passive";
}

EBTNodeResult::Type UBTTask_SetPassiveState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Cast<AEnemyAIController>((OwnerComp.GetAIOwner()))->SetPassiveState();
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_SetPassiveState::GetStaticDescription() const
{
	return "Sets state to passive";
}
