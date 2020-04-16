﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPS_TUTORIAL_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 前後方向移動
	UFUNCTION()
	void MoveForward(float Value);

	// 左右方向移動（右が正）
	UFUNCTION()
	void MoveRight(float Value);

	// ジャンプ開始
	UFUNCTION()
	void StartJump();

	// ジャンプ終了
	UFUNCTION()
	void EndJump();
};
