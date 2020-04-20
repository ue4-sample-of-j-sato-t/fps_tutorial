// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacterController.h"

AFPSCharacterController::AFPSCharacterController()
{
	Super();

	PrimaryActorTick.bCanEverTick = true;
}

void AFPSCharacterController::SetupInputComponent()
{
	InputComponent->BindAxis("MoveForward", this, &AFPSCharacterController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacterController::MoveRight);

	InputComponent->BindAxis("Turn", this, &AFPSCharacterController::TurnCamera);
	InputComponent->BindAxis("LookUp", this, &AFPSCharacterController::LookupCamera);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFPSCharacterController::StartJump);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AFPSCharacterController::EndJump);

	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AFPSCharacterController::FireProjectile);
}

void AFPSCharacterController::MoveForward(float AxisValue)
{
}

void AFPSCharacterController::MoveRight(float AxisValue)
{
}

void AFPSCharacterController::TurnCamera(float AxisValue)
{
}

void AFPSCharacterController::LookupCamera(float AxisValue)
{
}

void AFPSCharacterController::StartJump()
{
}

void AFPSCharacterController::EndJump()
{
}

void AFPSCharacterController::FireProjectile()
{
}

void AFPSCharacterController::Tick(float DeltaTime)
{
}
