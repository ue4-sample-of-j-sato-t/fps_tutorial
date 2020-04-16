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
