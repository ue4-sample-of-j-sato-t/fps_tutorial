// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "fps_tutorialGameModeBase.h"

#include "Engine.h"

void Afps_tutorialGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		// 画面上に出すログ
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hello world, this is FPSGameMode"));
	}
	
}
