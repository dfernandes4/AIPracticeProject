// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "AIState.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "BTTask_MoveAlongPatrolRoute.h"
#include "Perception/AIPerceptionComponent.h"
#include "Sense.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"

/* Includes for ChasePlayer() without blackboard/behavior tree.
 * 
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
*/

AEnemyAIController::AEnemyAIController()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	AttackTargetKey = "AttackTarget";
	SpawnTargetKey = "SpawnTarget";
	AIStateKey = "AIState";
	PointOfInterestKey = "PointOfInterest";
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (IsValid(BehaviorTree.Get()))
	{
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BehaviorTree is not valid"));
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsValid(Blackboard.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
		Blackboard->SetValueAsObject(AttackTargetKey, UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		
		if(const TObjectPtr<AActor> TargetActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATargetPoint::StaticClass()))
		{
			Blackboard->SetValueAsObject(SpawnTargetKey, TargetActor.Get());
			Blackboard->SetValueAsEnum(AIStateKey, static_cast<uint8>(EAIState::Passive));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TargetActor is not valid"));
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Blackboard is not valid"));
	}
}

void AEnemyAIController::SetAttackingState(AActor* AttackTarget) const
{
	Blackboard->SetValueAsEnum(AIStateKey,static_cast<uint8>(EAIState::Attacking));
	if(IsValid(AttackTarget))
	{
		Blackboard->SetValueAsObject(AttackTargetKey, AttackTarget);
	}
}


void AEnemyAIController::SetPassiveState() const
{
	Blackboard->SetValueAsEnum(AIStateKey, static_cast<uint8>(EAIState::Passive));
}

void AEnemyAIController::SetInvestigatingState(FVector& Location) const
{
	Blackboard->SetValueAsEnum(AIStateKey, static_cast<uint8>(EAIState::Investigating));
	Blackboard->SetValueAsVector(PointOfInterestKey, Location);
}

bool AEnemyAIController::CanSenseActor(AActor* Actor, const ESense Sense, FAIStimulus& SensedStimulusOut)
{
	const FActorPerceptionInfo* ActorPerceptionInfo = AIPerceptionComponent->GetActorInfo(*Actor);
	//Might need this				\/ Later on
	const TArray<FAIStimulus> Stimuli = ActorPerceptionInfo->LastSensedStimuli;
	for(const FAIStimulus SensedStimulus: Stimuli)
	{
		const TSubclassOf<UAISense> AISenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, SensedStimulus);
		switch(Sense)
		{
		case ESense::Seeing:
			if(AISenseClass == UAISense_Sight::StaticClass())
			{
				SensedStimulusOut = SensedStimulus;
				return SensedStimulus.WasSuccessfullySensed();
			}
			break;
		case ESense::Hearing:
			if(AISenseClass == UAISense_Hearing::StaticClass())
			{
				SensedStimulusOut = SensedStimulus;
				return SensedStimulus.WasSuccessfullySensed();
			}
			break;
		case ESense::Damaging:
			if(AISenseClass == UAISense_Damage::StaticClass())
			{
				SensedStimulusOut = SensedStimulus;
				return SensedStimulus.WasSuccessfullySensed();
			}
			break;
		default:
			break;
		}
	}
	return false;
}

void AEnemyAIController::HandleSensedSight(AActor* Actor)
{
	const EAIState CurrentState = GetCurrentState();
	switch(CurrentState)
	{
	case EAIState::Passive:
	case EAIState::Investigating:
		if(Actor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		{
			SetAttackingState(Actor);
		}
		break;
	default:
		break;
	}
}

void AEnemyAIController::HandleSensedSound(FVector& Location)
{
	const EAIState CurrentState = GetCurrentState();
	switch(CurrentState)
	{
	case EAIState::Passive:
	case EAIState::Investigating:
		SetInvestigatingState(Location);
		break;
	default:
		break;
	}
}

void AEnemyAIController::HandleSensedDamage()
{
	const EAIState CurrentState = GetCurrentState();
	switch(CurrentState)
	{
	case EAIState::Passive:
	case EAIState::Investigating:
		SetAttackingState(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		break;
	default:
		break;
	}
}

EAIState AEnemyAIController::GetCurrentState() const
{
	return static_cast<EAIState>(Blackboard->GetValueAsEnum(AIStateKey));
}

void AEnemyAIController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	Super::ActorsPerceptionUpdated(UpdatedActors);
	
	for (AActor* Actor : UpdatedActors)
	{
		if(CanSenseActor(Actor, ESense::Seeing, Stimulus))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "I Can See YOu" );
			HandleSensedSight(Actor);
		}
		if(CanSenseActor(Actor, ESense::Damaging, Stimulus))
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, "YOu hurt me!!!!" );
			HandleSensedDamage();
		}
		if(CanSenseActor(Actor, ESense::Hearing, Stimulus))
		{
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, "I Can Hear YOu" );
			HandleSensedSound(Stimulus.StimulusLocation);
		}
	}
}

/*
void AEnemyAIController::ChasePlayer()
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(Player != nullptr)
	{
		const EPathFollowingRequestResult::Type MoveResult = MoveToActor(Player, 5.0f);
		if(MoveResult == EPathFollowingRequestResult::Type::RequestSuccessful || MoveResult == EPathFollowingRequestResult::Type::AlreadyAtGoal)
		{
			UKismetSystemLibrary::Delay(this, 2.0f, FLatentActionInfo(0, 0, TEXT("ChasePlayer"), this));
			UE_LOG(LogTemp, Warning, TEXT("MoveToActor Succeded")) ;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MoveToActor failed"));
		}
	}
}
*/


