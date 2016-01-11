// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "StayAlive.h"
#include "StayAliveGameMode.h"
#include "StayAliveHUD.h"
#include "StayAliveCharacter.h"

AStayAliveGameMode::AStayAliveGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AStayAliveHUD::StaticClass();
}
