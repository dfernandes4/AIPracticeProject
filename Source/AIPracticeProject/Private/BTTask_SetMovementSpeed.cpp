// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetMovementSpeed.h"
#include "EnemyBase.h"

UBTTask_SetMovementSpeed::UBTTask_SetMovementSpeed()
{
	NodeName = "Set Movement Speed";
}

EBTNodeResult::Type UBTTask_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AEnemyBase> Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if(IsValid(Enemy.Get()))
	{
		Enemy->SetMovementSpeed(DesiredMovementSpeed);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}

FString UBTTask_SetMovementSpeed::GetStaticDescription() const
{
	return FString("Sets Movement Speed");
}
