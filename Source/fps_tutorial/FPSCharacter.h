// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacterInterface.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;
class AFPSProjectile;

UCLASS()
class FPS_TUTORIAL_API AFPSCharacter : public ACharacter, public IFPSCharacterInterface
{
	GENERATED_BODY()

private:
	// カメラ
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// 一人称用メッシュ
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	// 弾としてスポーンするクラス
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	// 発射位置指定用
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	UArrowComponent* ProjectileFirePoint;


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

	// 発射
	UFUNCTION()
	void Fire();

	// FPSCharacterInterface
	virtual void MoveIF(FVector Direction) override;
	virtual void RotationIF(FRotator Rotation) override;
	virtual void StartJumpIF() override;
	virtual void EndJumpIF() override;
	virtual void FireIF() override;
};
