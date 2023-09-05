// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIPracticeProjectGameMode.h"
#include "AIPracticeProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIPracticeProjectGameMode::AAIPracticeProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
