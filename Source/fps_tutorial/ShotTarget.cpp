// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotTarget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "FPSProjectile.h"

// Sets default values
AShotTarget::AShotTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// 当たったときの反応だけのはずなのでTickは切る

	Root = CreateDefaultSubobject<USceneComponent>("Root Component");
	RootComponent = Root;

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	TargetMesh->SetupAttachment(Root);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Target"));
	CollisionComponent->InitBoxExtent(FVector(50.f, 20.f, 50.f));
	CollisionComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AShotTarget::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddDynamic(this, &AShotTarget::OnHit);
}

void AShotTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NomalImpulse, const FHitResult& Hit)
{
	// 相手判定
	if (!Cast<AFPSProjectile>(OtherActor)) return;

	// 固有処理呼び出し
	OnProjectileHit();

	// 自身を削除
	Destroy();
}
