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

## アニメーション

※エディタ側の操作
1. アニメーションのインポート
1. アニメーションBPの作成
1. メッシュにセットする

### インポート

- 外部のファイル（fbxなど）にあるアニメーションをインポートする
- インポート時にアニメーションに対応するスケルトンを指定する
	- プレビューなどで指定したスケルトンとそれを使用するメッシュが表示される

### アニメーションBP作成

1. ステートを作成する
1. 遷移の流れを作成する
1. 遷移の条件を設定する

#### ステート作成

- アニメーションBP内AnimGraph内で右クリック->AddState
- 作成したステートをダブルクリックしてそのステートでのアニメーションを設定する
	- `Play (アニメーション名)`でアニメーションをセットできる
	- 最終的な結果は`OutputAnimationPose`に入れる
		- ここでブレンドなども可能？チュートリアルにはなかったので必要なら別途確認する

#### 処理の流れを作成する

- `Entry`から初期のステートに矢印を引く
	- 先はステートの四角の周りにある枠まで伸ばす
- 遷移元から遷移先のステートに矢印を引く
	- 同様に枠から枠まで伸ばす

#### 条件を設定する

- 引いた矢印にあるアイコンをダブルクリック
- booleanを返す関数になっているので、遷移するときにTrueを返すように設定する

- 条件の例
	- キャラクタの状態を使う
		- `EMovementMode Character->CharacterMovementComponent->MovementMode`
	- キャラクタの移動量を使う
		- `float Character->GetVelocity()->VectorLength()`
	- 現在のステートの残り時間
		- `float TimeRemaining(アニメーション名)()`

## よく詰まるところ

- ソース側の変更がBPに反映されたい
	- 元々あった設定がBP固有の設定として残ってしまう
	- 黄色の戻す矢印を押すとデフォルト（ソース側の設定）に戻る

## ex及び派生ブランチ

- ゲームにする

### ゲームルール・作成の条件

- 操作をコントローラに移す
	- ポーンに書いている処理を移す
	- コントローラからの呼び出しはインターフェースにする
- 時間制限な的撃ち
	- 位置はランダム
	- 移動は無し
		- ただし、後から追加ができるようにする
	- リロード追加
		- 残弾0で発射できなくする
		- リロード中は発射不可にする（リロードの中断は考えない）
		- リロードは特定のキーで実行する
- UI作成
	- 残り時間
	- スコア
	- 弾数
- アウトゲーム作成
	- タイトル-インゲームの相互

## 現状の問題点

- レティクルが機能していない
	- 画面中央を直進していない
		- 数値指定でなくArrowComponentを使う形に変更
- 開始前待機中のカメラが原点にいる
	- 専用のカメラを使う？
	- UIで隠す？


## エンジン側の関数をオーバーライドする

- **必ず**親クラスの関数を呼ぶ

```cpp
// APlayerController::OnPossess をオーバーライドする場合
void AFPSCharacterController::OnPossess(APawn* InPawn)
{
	// Superを使って親クラスの処理を呼ぶ
	Super::OnPossess(InPawn);

	/* 派生先の固有処理 */
}
```

## レベル遷移

- 遷移を行う処理をポーンに持たせる
- 遷移ができるようになったら上記ポーンを操作するようにする
- コントローラをインゲームとタイトルで共有化できる？

### 遷移させた際のバグ？

- キャラ？の当たり判定が消える？
	- 開始直後に床をすり抜け落ちてしまう
	- インゲームのレベルから開始すると問題ない
	- コントローラにセットしたタイミングから落ちている？
