// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FocusTarget.generated.h"

/**
 * 
 */
UCLASS()
class AIPRACTICEPROJECT_API UBTTask_FocusTarget : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTask_FocusTarget();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FName TargetActorKey = "TargetActor";
};
