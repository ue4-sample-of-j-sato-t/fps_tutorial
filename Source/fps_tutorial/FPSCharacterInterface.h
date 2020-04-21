// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FPSCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFPSCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPS_TUTORIAL_API IFPSCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
		移動
		@param Direction 移動方向（正規化を行うかは未定義）
	*/
	virtual void MoveIF(FVector Direction) {}

	/**
		回転
		@param Rotaion 回転設定
	*/
	virtual void RotationIF(FRotator Rotation) {}

	/**
		ジャンプ開始
	*/
	virtual void StartJumpIF() {}

	/**
		ジャンプ終了
	*/
	virtual void EndJumpIF() {}

	/**
		発射
	*/
	virtual void FireIF() {}
};
