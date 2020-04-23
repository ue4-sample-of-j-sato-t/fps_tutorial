// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TUTORIAL_API ATitleGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly)
    FName PlayLevelPath;

public:

    ATitleGameMode();

    UFUNCTION(BlueprintCallable)
    void MovePlayLevel();
};
