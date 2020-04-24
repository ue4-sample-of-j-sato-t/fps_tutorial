// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleController.h"

void ATitleController::OnShootInput()
{
	OnShootEvent.Broadcast();
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
