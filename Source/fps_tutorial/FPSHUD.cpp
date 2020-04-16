// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHUD.h"
#include "Engine/Canvas.h"

void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	// テクスチャがなければ中止
	if (CrosshairTexture == nullptr) return;

	// キャンバスの中心
	FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// テクスチャを中央に表示するための座標
	FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

	// 中心にテクスチャを描画
	FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}
