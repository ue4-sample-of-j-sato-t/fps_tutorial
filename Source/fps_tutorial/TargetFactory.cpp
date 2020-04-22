// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetFactory.h"
#include "Components/BoxComponent.h"
#include "ShotTarget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"

// Sets default values
ATargetFactory::ATargetFactory()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(SceneComponent);
	SpawnArea->BodyInstance.SetCollisionProfileName("NoCollision");

	SpawnMinSec = 1.f;
	SpawnMaxSec = 2.f;
}

void ATargetFactory::SetupNextSpawnTime()
{
	// パラメータのセーフティ
	if (SpawnMinSec > SpawnMaxSec)
	{
		float Temp = SpawnMinSec;
		SpawnMinSec = SpawnMaxSec;
		SpawnMaxSec = Temp;
	}

	// 次にスポーンする時間をセット
	NextSpawnSec = FMath::RandRange(SpawnMinSec, SpawnMaxSec);
}

void ATargetFactory::CheckSpawnTime(float DeltaTime)
{
	NextSpawnSec -= DeltaTime;

	if (NextSpawnSec < 0.f)
	{
		SpawnTarget();
		SetupNextSpawnTime();
	}
}

void ATargetFactory::SpawnTarget()
{
	// ワールド取得
	UWorld* World = GetWorld();
	if (!World)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No world"));
		return;
	}

	// 的クラスチェック
	if (TargetActorClass == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("TargetClass disable"));
		return;
	}

	// 生成位置
	FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->GetRelativeLocation(), SpawnArea->GetScaledBoxExtent());
	// アクタからの相対座標へ
	SpawnLocation = GetActorLocation() + (GetActorRotation().RotateVector(SpawnLocation));
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, SpawnLocation.ToString());

	// 生成
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.Instigator = Instigator;

	AShotTarget* Target = World->SpawnActor<AShotTarget>(TargetActorClass, SpawnLocation, GetActorRotation(), SpawnParam);
}

// Called when the game starts or when spawned
void ATargetFactory::BeginPlay()
{
	Super::BeginPlay();
	
	SetupNextSpawnTime();
}

// Called every frame
void ATargetFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckSpawnTime(DeltaTime);
}

