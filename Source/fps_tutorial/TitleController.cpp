// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleController.h"
#include "GameFramework/Pawn.h"
#include "FPSCharacterInterface.h"

void ATitleController::OnShootInput()
{
	APawn* MyPawn = GetPawn<APawn>();
	if (MyPawn && MyPawn->GetClass()->ImplementsInterface(UFPSCharacterInterface::StaticClass()))
	{
		Cast<IFPSCharacterInterface>(MyPawn)->FireIF();
	}


	//OnShootEvent.Broadcast();
	//UnPossess();
}

void ATitleController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATitleController::OnShootInput);
}

void ATitleController::BindToOnShootEvent(FOnShootEvent::FDelegate& InDelegate)
{
	OnShootEvent.Add(InDelegate);
}
