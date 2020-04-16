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

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 軸イベントのバインド
	// - 移動
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// - 視点
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// アクションイベントのバインド
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AFPSCharacter::EndJump);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForward(float Value)
{
	// 前方方向
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	// 移動
	AddMovementInput(Direction * Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	// 右方向
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	// 移動
	AddMovementInput(Direction * Value);
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

	// 発射位置の取得 -> カメラ位置 + カメラに合わせて回転させたマズル相対位置
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
	FRotator MuzzleRotation = CameraRotation;
	// 発射方向調整
	MuzzleRotation.Pitch += 10.f;

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
