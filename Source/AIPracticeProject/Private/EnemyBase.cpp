// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "MovementSpeed.h"
#include "Sword.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsWieldingSword = false;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	//Possessing the AIController
	if(IsValid(EnemyAIControllerClass))
	{
		if(AEnemyAIController* EnemyAIController = GetWorld()->SpawnActor<AEnemyAIController>(EnemyAIControllerClass, GetActorLocation(), GetActorRotation()))
		{
			EnemyAIController->Possess(this);
			//EnemyAIController->ChasePlayer();
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("EnemyAIController is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyAIControllerClass is nullptr"));
	}
	
}

void AEnemyBase::WieldSword()
{
	const TObjectPtr<ASword> SwordActor = GetWorld()->SpawnActor<ASword>(SwordClass, GetActorLocation(), GetActorRotation());
	if(IsValid(SwordActor.Get()))
	{
		SwordActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_r_sword_socket"));
	}
	bIsWieldingSword = true;
}

void AEnemyBase::UnWieldSword()
{
	const TObjectPtr<ASword> SwordActor = Cast<ASword>(UGameplayStatics::GetActorOfClass(this, ASword::StaticClass()));
	if(IsValid(SwordActor.Get()))
	{
		UE_LOG(LogTemp, Warning, TEXT("The Sword should be deleted"));
		SwordActor->Destroy();
		bIsWieldingSword = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Sword is not valid"));
	}
	
}

bool AEnemyBase::GetIsWieldingSword() const
{
	return bIsWieldingSword;
}

APatrolRoute* AEnemyBase::GetPatrolRoute()
{
	return PatrolRoute.Get();
}

float AEnemyBase::SetMovementSpeed(const EMovementSpeed Speed)
{
	switch(Speed)
	{
	case EMovementSpeed::Idle:
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		break;
	case EMovementSpeed::Walk:
		GetCharacterMovement()->MaxWalkSpeed = 100.f;
		break;
	case EMovementSpeed::Run:
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		break;
	case EMovementSpeed::Sprint:
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
		break;
	}
	return GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



