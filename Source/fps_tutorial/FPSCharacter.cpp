// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"
#include "FPSProjectile.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// カメラ作成
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	// カメラ位置調整
	FPSCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f + BaseEyeHeight));
	// ポーンがカメラの回転を制御できるようにする
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 一人称用メッシュ
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	// 所持者のみに表示
	FPSMesh->SetOnlyOwnerSee(true);
	// カメラにアタッチ
	FPSMesh->SetupAttachment(FPSCameraComponent);
	// このメッシュでシャドウを作らないようにする
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// 発射位置
	ProjectileFirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	ProjectileFirePoint->SetupAttachment(FPSCameraComponent);
	ProjectileFirePoint->SetRelativeLocationAndRotation(FVector(150.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("we are using FPSChearacter"));
	}

	// 三人称用メッシュ
	// 所持者から見えなくする
	GetMesh()->SetOwnerNoSee(true);
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// カメラはTickでないと動かない？
	AddControllerYawInput(CameraInput.Yaw);
	AddControllerPitchInput(CameraInput.Pitch);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	// ワールドの取得ができなければ中止
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	// 弾のクラスがセットされていなかったら中止
	if (ProjectileClass == nullptr) return;

	// 現在のカメラ情報保持
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	// 発射位置の調整：ArrowComponentの位置・回転を使用
	FVector MuzzleLocation = ProjectileFirePoint->GetComponentLocation();
	FRotator MuzzleRotation = ProjectileFirePoint->GetComponentRotation();

	// - 以下生成

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.Instigator = Instigator;

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParam);
	if (Projectile)
	{
		// 初期設定
		FVector LaunchDirection = MuzzleRotation.Vector();
		Projectile->FireInDirection(LaunchDirection);
	}
}

void AFPSCharacter::MoveIF(FVector Direction)
{
	FVector MoveDirection = GetActorRotation().RotateVector(Direction);
	MoveDirection.Normalize();

	AddMovementInput(MoveDirection);
}

void AFPSCharacter::RotationIF(FRotator Rotation)
{
	CameraInput = Rotation;
}

void AFPSCharacter::StartJumpIF()
{
	StartJump();
}

void AFPSCharacter::EndJumpIF()
{
	EndJump();
}

void AFPSCharacter::FireIF()
{
	Fire();
}
