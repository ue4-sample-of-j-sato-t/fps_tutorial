// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetFactory.generated.h"

class AShotTarget;
class UBoxComponent;

UCLASS()
class FPS_TUTORIAL_API ATargetFactory : public AActor
{
	GENERATED_BODY()

private:
	// 次にスポーンするまでの時間（秒）
	float NextSpawnSec;

public:
	// 配置する的クラス
	UPROPERTY(EditAnywhere, Category = "Factory")
	TSubclassOf<class AShotTarget> TargetActorClass;

	// 配置する領域
	UPROPERTY(EditDefaultsOnly, Category = "Factory")
	UBoxComponent* SpawnArea;

	// スポーンする最小間隔（秒）
	UPROPERTY(EditAnywhere, Category = "Factory/SpawnTime")
	float SpawnMinSec;
	// スポーンする最大間隔（秒）
	UPROPERTY(EditAnywhere, Category = "Factory/SpawnTime")
	float SpawnMaxSec;

public:	
	// Sets default values for this actor's properties
	ATargetFactory();

private:

	// 次回のスポーンまでの間隔を決める
	void SetupNextSpawnTime();

	// 今回スポーンするかを判断する
	void CheckSpawnTime(float DeltaTime);

	// 領域内に的アクタをスポーンする
	void SpawnTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
