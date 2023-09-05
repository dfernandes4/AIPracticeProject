// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"


enum class ESense : uint8;
enum class EAIState : uint8;
class ATargetPoint;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class AIPRACTICEPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
/*
 * Implementations without blackboard/behavior tree.
 * 
	UFUNCTION(BlueprintCallable, Category = "Functions")
	void ChasePlayer();
*/

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	void SetAttackingState(AActor* AttackTarget) const;
	void SetPassiveState() const;
	void SetInvestigatingState(FVector& Location) const;
	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;
	UFUNCTION()
	bool CanSenseActor( AActor* Actor, const ESense Sense, FAIStimulus& SensedStimulusOut);
	UFUNCTION()
	void HandleSensedSight(AActor* Actor);
	UFUNCTION()
	void HandleSensedSound(FVector& Location);
	UFUNCTION()
	void HandleSensedDamage();
	UFUNCTION()
	EAIState GetCurrentState() const;
	
private:
	// AI Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	
	//Blackboard Keys
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackboardKeys", meta = (AllowPrivateAccess = "true"))
	FName AttackTargetKey;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackboardKeys", meta = (AllowPrivateAccess = "true"))
	FName SpawnTargetKey;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackboardKeys", meta = (AllowPrivateAccess = "true"))
	FName AIStateKey;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackboardKeys", meta = (AllowPrivateAccess = "true"))
	FName PointOfInterestKey;

	//Class Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ClassVariables", meta = (AllowPrivateAccess = "true"))
	FAIStimulus Stimulus;
	

	AEnemyAIController();
};
