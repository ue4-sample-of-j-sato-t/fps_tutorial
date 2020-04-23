// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleGameMode.h"
#include "Kismet/GameplayStatics.h"

ATitleGameMode::ATitleGameMode() : Super()
{
	// デフォルトを外す
	DefaultPawnClass = nullptr;
}

void ATitleGameMode::MovePlayLevel()
{
	UGameplayStatics::OpenLevel(this, PlayLevelPath);
}