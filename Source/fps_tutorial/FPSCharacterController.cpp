﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacterController.h"
#include "GameFramework/Pawn.h"
#include "Engine.h"

AFPSCharacterController::AFPSCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;

	MoveDirection = FVector(0.f);
	Rotation = FRotator(0.f);

	CharacterInterface = nullptr;

	SetIgnoreLookInput(false);
}

void AFPSCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AFPSCharacterController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacterController::MoveRight);

	InputComponent->BindAxis("Turn", this, &AFPSCharacterController::TurnCamera);
	InputComponent->BindAxis("LookUp", this, &AFPSCharacterController::LookupCamera);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFPSCharacterController::StartJump);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AFPSCharacterController::EndJump);

	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AFPSCharacterController::FireProjectile);
	InputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &AFPSCharacterController::Reload);
}

void AFPSCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn->GetClass()->ImplementsInterface(UFPSCharacterInterface::StaticClass()))
	{
		CharacterInterface = Cast<IFPSCharacterInterface>(InPawn);
	}
	else
	{
		CharacterInterface = nullptr;
	}
}

void AFPSCharacterController::OnUnPossess()
{
	Super::OnUnPossess();

	// 操作できなくする
	CharacterInterface = nullptr;
}

void AFPSCharacterController::MoveForward(float AxisValue)
{
	MoveDirection.X = AxisValue;
}

void AFPSCharacterController::MoveRight(float AxisValue)
{
	MoveDirection.Y = AxisValue;
}

void AFPSCharacterController::TurnCamera(float AxisValue)
{
	Rotation.Yaw = AxisValue;
}

void AFPSCharacterController::LookupCamera(float AxisValue)
{
	Rotation.Pitch = AxisValue;
}

void AFPSCharacterController::StartJump()
{
	if (!CharacterInterface) return;
	CharacterInterface->StartJumpIF();
}

void AFPSCharacterController::EndJump()
{
	if (!CharacterInterface) return;
	CharacterInterface->EndJumpIF();
}

void AFPSCharacterController::FireProjectile()
{
	if (!CharacterInterface) return;
	CharacterInterface->FireIF();
}

void AFPSCharacterController::Reload()
{
	if (!CharacterInterface)return;
	CharacterInterface->ReloadIF();
}

void AFPSCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CharacterInterface) return;
	CharacterInterface->MoveIF(MoveDirection);
	CharacterInterface->RotationIF(Rotation);
}
