// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacterController.h"
#include "GameFramework/Pawn.h"

AFPSCharacterController::AFPSCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;

	MoveDirection = FVector(0.f);
	Rotation = FRotator(0.f);

	CharacterInterface = nullptr;
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
}

void AFPSCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 一旦クリア
	CharacterInterface = nullptr;

	if (InPawn->GetClass()->ImplementsInterface(UFPSCharacterInterface::StaticClass()))
	{
		CharacterInterface = Cast<IFPSCharacterInterface>(InPawn);
	}
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
	Rotation.Pitch = AxisValue;
}

void AFPSCharacterController::LookupCamera(float AxisValue)
{
	Rotation.Yaw = AxisValue;
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

void AFPSCharacterController::Tick(float DeltaTime)
{
	if (!CharacterInterface) return;
	CharacterInterface->MoveIF(MoveDirection);
	CharacterInterface->RotationIF(Rotation);
}
