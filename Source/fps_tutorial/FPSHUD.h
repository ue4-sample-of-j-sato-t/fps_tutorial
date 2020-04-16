// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TUTORIAL_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	// 中央に表示するレティクル
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

public:

	// プライマリドローコール
	virtual void DrawHUD() override;
};
