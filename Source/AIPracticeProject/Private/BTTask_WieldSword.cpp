// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WieldSword.h"
#include "EnemyBase.h"

EBTNodeResult::Type UBTTask_WieldSword::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyBase* EnemyBase = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (EnemyBase)
	{
		EnemyBase->WieldSword();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

FString UBTTask_WieldSword::GetStaticDescription() const
{
	return FString("Makes enemy wield a sword");
}
