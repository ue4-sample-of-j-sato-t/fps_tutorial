// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSCharacterInterface.h"
#include "FPSCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TUTORIAL_API AFPSCharacterController : public APlayerController
{
	GENERATED_BODY()
private:
	// 移動量
	FVector MoveDirection;

	// 回転量
	FRotator Rotation;

	// インターフェースへのキャッシュ
	IFPSCharacterInterface* CharacterInterface;

public:
	AFPSCharacterController();
	
protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

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
