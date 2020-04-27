// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChangePawn.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ALevelChangePawn::ALevelChangePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bCanMoveLevel = true;
}


void ALevelChangePawn::FireIF()
{
	if (!bCanMoveLevel)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Disable move level!"));
		return;
	}

	UGameplayStatics::OpenLevel(this, NextLevelPath);
}
