// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tutorial1GameMode.h"
#include "Tutorial1HUD.h"
#include "Tutorial1Character.h"
#include "UObject/ConstructorHelpers.h"

ATutorial1GameMode::ATutorial1GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATutorial1HUD::StaticClass();
}
