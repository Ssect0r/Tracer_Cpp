// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Tracer_cppGameMode.h"
#include "Tracer_cppHUD.h"
#include "Tracer_cppCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATracer_cppGameMode::ATracer_cppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	// use our custom HUD class
	HUDClass = ATracer_cppHUD::StaticClass();
}
