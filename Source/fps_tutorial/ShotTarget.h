// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShotTarget.generated.h"

class UBoxComponent;

UCLASS()
class FPS_TUTORIAL_API AShotTarget : public AActor
{
	GENERATED_BODY()

private:

	// ルート
	USceneComponent* Root;

	// 表示物
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TargetMesh;

	// 判定
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionComponent;
	
public:	
	// Sets default values for this actor's properties
	AShotTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NomalImpulse, const FHitResult& Hit);

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "FPS")
	void OnProjectileHit();
};
