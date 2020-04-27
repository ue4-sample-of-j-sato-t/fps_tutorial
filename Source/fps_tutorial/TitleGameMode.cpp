// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "TitleController.h"


ATitleGameMode::ATitleGameMode() : Super()
{
	// デフォルトを外す
	DefaultPawnClass = nullptr;

	PlayerControllerClass = ATitleController::StaticClass();
}

void ATitleGameMode::MovePlayLevel()
{
	UGameplayStatics::OpenLevel(this, PlayLevelPath);
}

void ATitleGameMode::StartPlay()
{
	Super::StartPlay();

	//auto Controller = UGameplayStatics::GetActorOfClass(this, ATitleController::StaticClass());
	//ATitleController* TargetController = Cast<ATitleController>(Controller);
	//if (TargetController)
	//{
	//	FOnShootEvent::FDelegate UseEventDelegate;
	//	UseEventDelegate.BindDynamic(this, &ATitleGameMode::MovePlayLevel);
	//	TargetController->BindToOnShootEvent(UseEventDelegate);
	//}
}
