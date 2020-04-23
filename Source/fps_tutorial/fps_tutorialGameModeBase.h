// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "fps_tutorialGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EGameTiming : uint8
{
	BEFOR_GAME,
	RUNNING_GAME,
	AFTER_GAME,
	INITIALIZE,
	MAX,
};

DECLARE_DELEGATE_OneParam(TickDelegate, float)
class ATargetFactory;

/**
 * 
 */
UCLASS()
class FPS_TUTORIAL_API Afps_tutorialGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	Afps_tutorialGameModeBase(const FObjectInitializer& ObjectInitializer);

protected:
	// 現在の状況
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EGameTiming GameTiming;

	// 制限時間設定
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State|Timer")
	float MaxTimeLimit;
	// 残り時間
	UPROPERTY(BlueprintReadOnly, Category = "State|Timer")
	float LastTimeLimit;

	// スコア
	UPROPERTY(BlueprintReadWrite, Category = "State|Score")
	int32 Score;

	// 的生成アクタ
	TArray<ATargetFactory*> TargetFactorys;


	// 開始前待機時間
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State|Befor")
	float BeforWaitTime;
	// 残り待機時間
	float LastBeforWaitTime;

	// 最後に外されたPawn
	APawn* LastPossessedPawn;

private:
	
	// 的生成アクタ保持
	void HoldTargetFactorys();
	// 的生成アクタのTickを一括で変更
	void SetTickableToFactorys(bool bNewTickable);

	// コントローラからポーンを外す
	void UnPossessController();
	// コントローラにキャラをセット
	void PossessController();



	// tick用関数
	void TickBefor(float DeltaTime);
	void TickRunning(float DeltaTime);
	void TickAfter(float DeltaTime);

	// 開始関数
	void StartBefor();
	void StartRunning();
	void StartAfter();

public:

	virtual void StartPlay() override;
	virtual void Tick(float DeltaTime) override;

	void AddScore(int32 InAddScore = 1);
};
