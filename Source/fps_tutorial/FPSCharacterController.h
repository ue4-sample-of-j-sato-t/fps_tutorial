// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TUTORIAL_API AFPSCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	AFPSCharacterController();
	
protected:
	virtual void SetupInputComponent() override;

private:

	// 入力バインド
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void TurnCamera(float AxisValue);
	void LookupCamera(float AxisValue);

	void StartJump();
	void EndJump();

	void FireProjectile();

public:
	virtual void Tick(float DeltaTime) override;
};
