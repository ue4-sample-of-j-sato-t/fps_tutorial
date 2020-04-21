// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotTarget.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AShotTarget::AShotTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// 当たったときの反応だけのはずなのでTickは切る

	Root = CreateDefaultSubobject<USceneComponent>("Root Component");
	Root->SetupAttachment(RootComponent);

	TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	TargetMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AShotTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShotTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

