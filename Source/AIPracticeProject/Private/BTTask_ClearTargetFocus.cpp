// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearTargetFocus.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearTargetFocus::UBTTask_ClearTargetFocus()
{
	NodeName = "Clear Focus On Target";
}

EBTNodeResult::Type UBTTask_ClearTargetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AAIController> AIController {OwnerComp.GetAIOwner()};

	AIController->ClearFocus(EAIFocusPriority::Gameplay);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_ClearTargetFocus::GetStaticDescription() const
{
	return FString("Clears Focus from the target actor");
}