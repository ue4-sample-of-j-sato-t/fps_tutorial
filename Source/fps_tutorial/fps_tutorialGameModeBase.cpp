// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "fps_tutorialGameModeBase.h"

#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "TargetFactory.h"
#include "LevelChangePawn.h"

Afps_tutorialGameModeBase::Afps_tutorialGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	MaxTimeLimit = 30.f;

	Score = 0;

	BeforWaitTime = 5.f;
}

void Afps_tutorialGameModeBase::HoldTargetFactorys()
{
	TargetFactorys.Empty();

	TArray<AActor*> Emitters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetFactory::StaticClass(), Emitters);

	for (auto Actor : Emitters)
	{
		ATargetFactory* Factory = Cast<ATargetFactory>(Actor);
		
		// 念の為チェック
		if (!Factory) continue;

		TargetFactorys.Add(Factory);
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Holded factory num : ") + FString::FromInt(TargetFactorys.Num()));
}

void Afps_tutorialGameModeBase::SetTickableToFactorys(bool bNewTickable)
{
	for (auto Factory : TargetFactorys)
	{
		Factory->SetActorTickEnabled(bNewTickable);
	}
}

void Afps_tutorialGameModeBase::UnPossessController()
{
	auto Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (!Controller)return;

	// 使用していたポーンを保持
	auto NowPossessPawn = Controller->GetPawn();
	if (NowPossessPawn)LastPossessedPawn = NowPossessPawn;

	Controller->UnPossess();
}

void Afps_tutorialGameModeBase::PossessController()
{
	auto Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (!Controller)return;

	if (!LastPossessedPawn)return;
	Controller->Possess(LastPossessedPawn);
}

void Afps_tutorialGameModeBase::SpawnAndSetToTitle()
{
	// 設定確認
	if (!ToTitlePawnClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No set ToTitlePawnClass"));
		return;
	}

	// スポーン
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	ALevelChangePawn* ToTitlePawn = GetWorld()->SpawnActor<ALevelChangePawn>(ToTitlePawnClass, LastPossessedPawn->GetActorLocation(), LastPossessedPawn->GetActorRotation(), SpawnParams);
	if (!ToTitlePawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Fail spawn ToTitlePawn"));
		return;
	}

	// 接続
	auto Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (!Controller)return;

	Controller->Possess(ToTitlePawn);
}

void Afps_tutorialGameModeBase::TickBefor(float DeltaTime)
{
	LastBeforWaitTime -= DeltaTime;

	if (LastBeforWaitTime <= 0.f)
	{
		GameTiming = EGameTiming::RUNNING_GAME;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Game Start!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Cyan, TEXT("WaitTime : ") + FString::SanitizeFloat(LastBeforWaitTime));
	}
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
	SetTickableToFactorys(false);
	UnPossessController();
}

void Afps_tutorialGameModeBase::StartRunning()
{
	SetTickableToFactorys(true);
	PossessController();
}

void Afps_tutorialGameModeBase::StartAfter()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("SCORE : ") + FString::FromInt(Score));

	//UnPossessController();
	SpawnAndSetToTitle();

	SetTickableToFactorys(false);
}

void Afps_tutorialGameModeBase::StartPlay()
{
	Super::StartPlay();

	LastTimeLimit = MaxTimeLimit;
	LastBeforWaitTime = BeforWaitTime;

	HoldTargetFactorys();

	if (GEngine)
	{
		// 画面上に出すログ
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hello world, this is FPSGameMode"));
	}

	// 最初のステートをセット
	GameTiming = EGameTiming::INITIALIZE;
}

void Afps_tutorialGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EGameTiming BeforTiming = GameTiming;

	static bool lWaitInitialize = false;

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
	case EGameTiming::INITIALIZE:
		if (lWaitInitialize)	GameTiming = EGameTiming::BEFOR_GAME;
		else lWaitInitialize = true;
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
			lWaitInitialize = false;
			break;
		case EGameTiming::AFTER_GAME:
			StartAfter();
			break;
		default:
			break;
		}
	}
}

void Afps_tutorialGameModeBase::AddScore(int32 InAddScore)
{
	if (GameTiming != EGameTiming::RUNNING_GAME)return;

	if (InAddScore <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("disable add score"));
		return;
	}
	Score += InAddScore;

	OnUpdateScore.Broadcast(Score);
}
