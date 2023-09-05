// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FocusTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FocusTarget::UBTTask_FocusTarget()
{
	NodeName = "Focus On Target";
	TargetActorKey = "AttackTarget";
}

EBTNodeResult::Type UBTTask_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AAIController> AIController {OwnerComp.GetAIOwner()};
	const TObjectPtr<AActor> TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey));

	AIController->SetFocus(TargetActor.Get());
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_FocusTarget::GetStaticDescription() const
{
	return FString("Focuses the AI on the target actor");
}
