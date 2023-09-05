// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_IsPatrolling.h"
#include "GameFramework/Character.h"
#include "EnemyAI.h"
#include "PatrolRoute.h"
#include "AIController.h"

bool UBTD_IsPatrolling::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const TObjectPtr<APawn> OwnerPawn {Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn())};
	if(IsValid(OwnerPawn.Get()))
	{
		if(OwnerPawn->GetVelocity().IsNearlyZero())
		{
			return false;
		}
	}
	return true;
}
