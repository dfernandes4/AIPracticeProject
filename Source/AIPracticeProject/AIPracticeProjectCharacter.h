// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AIPracticeProjectCharacter.generated.h"


UCLASS(config=Game)
class AAIPracticeProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Explosion Template */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ParticleSystem, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> ExplosionTemplate;

	/** Explosion Sound */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SoundSystem, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> ExplosionSound;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

#pragma region Input Action
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Switch State Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SwitchStateAction;

	/** Explode Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ExplodeAction;

	/** Damage Enemy Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DamageEnemyAction;

#pragma endregion Input Action
	
	//For Switching States
	UPROPERTY()
	bool FlipFlop = true;

	UPROPERTY()
	TObjectPtr<class AEnemyBase> Enemy;

public:
	AAIPracticeProjectCharacter();
	

protected:
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Input Action Methods
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for switching state input */
	void SwitchState(const FInputActionValue& Value);

	/** Called for explode input */
	void Explode(const FInputActionValue& Value);

	/** Called for explode input */
	void DamageEnemy(const FInputActionValue& Value);

#pragma endregion Input Action Methods
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

