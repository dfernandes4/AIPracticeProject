// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDIsWieldingSword.h"
#include "AIController.h"
#include "EnemyBase.h"

bool UBTDIsWieldingSword::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const TObjectPtr<AEnemyBase> Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if(IsValid(Enemy.Get()))
	{
		return Enemy->GetIsWieldingSword();
	}
	return false;
}
