// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "fps_tutorialGameModeBase.h"

#include "Engine.h"
#include "Kismet/GameplayStatics.h"

Afps_tutorialGameModeBase::Afps_tutorialGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	GameTiming = EGameTiming::BEFOR_GAME;

	MaxTimeLimit = 30.f;
	LastTimeLimit = MaxTimeLimit;
}

void Afps_tutorialGameModeBase::TickBefor(float DeltaTime)
{
	// TODO 開始前待機
	GameTiming = EGameTiming::RUNNING_GAME;
}

void Afps_tutorialGameModeBase::TickRunning(float DeltaTime)
{
	LastTimeLimit -= DeltaTime;
	if (LastTimeLimit < 0.f)
	{
		GameTiming = EGameTiming::AFTER_GAME;
	}
}

void Afps_tutorialGameModeBase::TickAfter(float DeltaTime)
{
	// TODO 終了後処理
}

void Afps_tutorialGameModeBase::StartBefor()
{
}

void Afps_tutorialGameModeBase::StartRunning()
{
}

void Afps_tutorialGameModeBase::StartAfter()
{
	auto Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (!Controller)return;
	Controller->UnPossess();
}

void Afps_tutorialGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		// 画面上に出すログ
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hello world, this is FPSGameMode"));
	}
}

void Afps_tutorialGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EGameTiming BeforTiming = GameTiming;

	switch (GameTiming)
	{
	case EGameTiming::RUNNING_GAME:
		TickRunning(DeltaTime);
		break;
	case EGameTiming::BEFOR_GAME:
		TickBefor(DeltaTime);
		break;
	case EGameTiming::AFTER_GAME:
		TickAfter(DeltaTime);
		break;
	default:
		break;
	}

	if (BeforTiming != GameTiming)
	{
		switch (GameTiming)
		{
		case EGameTiming::RUNNING_GAME:
			StartRunning();
			break;
		case EGameTiming::BEFOR_GAME:
			StartBefor();
			break;
		case EGameTiming::AFTER_GAME:
			StartAfter();
			break;
		default:
			break;
		}
	}
}
