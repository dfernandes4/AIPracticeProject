// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAI.h"
#include "EnemyAIController.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class APatrolRoute;
struct FAIRequestID;
struct FPathFollowingResult;
class ASword;

UCLASS()
class AIPRACTICEPROJECT_API AEnemyBase : public ACharacter, public IEnemyAI
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region AttackingFunctions
	
	UFUNCTION(Category = "Functions")
	void WieldSword();
	UFUNCTION(Category = "Functions")
	void UnWieldSword();
	UFUNCTION(BlueprintCallable, Category = "Functions")
	bool GetIsWieldingSword() const;

#pragma endregion AttackingFunctions

#pragma region IEnemyAIFunctions
	
	virtual APatrolRoute* GetPatrolRoute() override;
	virtual float SetMovementSpeed(const EMovementSpeed Speed) override;
	
#pragma endregion IEnemyAIFunctions
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AEnemyAIController> EnemyAIControllerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<ASword> SwordClass;
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<APatrolRoute> PatrolRoute;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bIsWieldingSword;
};
