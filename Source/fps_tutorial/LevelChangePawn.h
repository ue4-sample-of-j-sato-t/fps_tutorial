// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FPSCharacterInterface.h"
#include "LevelChangePawn.generated.h"

UCLASS()
class FPS_TUTORIAL_API ALevelChangePawn : public APawn, public IFPSCharacterInterface
{
	GENERATED_BODY()


protected:
	
	/**
		遷移先レベル
		@note "/Game"からのパスで、"アセット名.アセット名"にする
	*/
	UPROPERTY(EditDefaultsOnly, Category = "LevelChange")
	FName NextLevelPath;

	/**
		セーフティフラグ
		@note falseのときは遷移を行わない
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelChange")
	bool bCanMoveLevel;

public:
	// Sets default values for this pawn's properties
	ALevelChangePawn();


	// 発射ボタンイベントとしてレベル遷移を行う
	virtual void FireIF() override;
};
