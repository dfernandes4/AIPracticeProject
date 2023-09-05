// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TeleportToRandomLocation.generated.h"

class ATargetPoint;
/**
 * 
 */
UCLASS()
class AIPRACTICEPROJECT_API UBTTask_TeleportToRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_TeleportToRandomLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
