# fps_tutorial
https://docs.unrealengine.com/ja/Programming/Tutorials/FirstPersonShooter/index.html

## 画面上のログ

```cpp
#include "Engine.h"

	//(キー, 表示時間, 色, 表示文字列)
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hello world, this is FPSGameMode"));
```

## イベントのバインド

- プロジェクト設定の入力設定でアクションイベントや軸イベントの設定が必要

```cpp
// Pawn以降のクラスで実装する
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 軸イベントのバインド
	// - 独自の関数にバインド
	//   - (イベント名, どのオブジェクトか, どのメソッドか)
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);

	// アクションイベントのバインド
	//   - （イベント名, 押されたときか離されたときか, どのオブジェクトか, どのメソッドか）
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFPSCharacter::Jump)
}
```

## 移動などの関数

### 移動
```cpp
void AFPSCharacter::MoveForward(float Value)
{
	// 現在の正面方向
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	// 移動
	AddMovementInput(Direction * Value);
}
void AFPSCharacter::MoveRight(float Value)
{
	// 現在の正面に対しての右方向
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	// 移動
	AddMovementInput(Direction * Value);
}
```
### カメラ移動

- ここでは`Pawn`が最初から持っているメソッドを使用した
- `AddControllerYawInput`
	- 左右方向の回転
- `AddControllerPitchInput`
	- 上下方向の回転

## メッシュ表示制御

### 所有者から見て
```cpp
// 所有者にのみ表示
FPSMesh->SetOnlyOwnerSee(true);

// 所有者にのみ非表示
// ※コンストラクタでなく BeginPlay で実行する
GetMesh()->SetOwnerNoSee(true);
```

## 当たり判定

1. 判定チャンネル作成
1. チャンネル用プリセット作成
1. ヒット処理バインド

### チャンネル作成

1. ProjectSetting -> Engine -> Collision
1. NewObjectChannel
1. 名前と、他チャンネルオブジェクトとの接触時のデフォルト設定を入れる

### プリセット作成

1. 同画面Preset欄のNew
1. 名前と判定が有効か、どのチャンネルかをセットする
1. 他のチャンネルとの接触時の反応を個別で設定する

### ヒット処理バインド

```cpp
	// コンストラクタ等でバインド
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
```

```cpp
	// 関数シグネチャ
	UFUNCTION() // 付け忘れない
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NomalImpulse, const FHitResult& Hit);
	/*
		HitComponent : 自身のどのコンポーネントに当たったか
		OtherActor : 接触相手のActor
		OtherComponent : 接触相手のどのコンポーネントに当たったか
		NomalImpulse : アクタの衝突する力
		Hit : 衝突に関する詳細情報
	 */


	 // 実装例：当たったアクタに衝撃を与えて弾く
	 if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		// 自身の速度をもとにした力を衝突した点に加える（衝突相手のその後の動きは物理演算で）
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.f, Hit.ImpactPoint);
	}
```

## HUD

- テクスチャ等を2DGUIとして画面に描画する
	- 動きの少ない表示はこちらがいい？
	- 動きのあるときはUMGの方が使いやすい？

### 描画処理

- セットされたテクスチャを画面中央に表示する

```cpp
void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	// テクスチャがなければ中止
	if (CrosshairTexture == nullptr) return;

	// キャンバス（画面）の中心
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// テクスチャを中央に表示するための座標
	FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

	// 中心にテクスチャを描画
	FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}
```

## よく詰まるところ

- ソース側の変更がBPに反映されたい
	- 元々あった設定がBP固有の設定として残ってしまう
	- 黄色の戻す矢印を押すとデフォルト（ソース側の設定）に戻る
