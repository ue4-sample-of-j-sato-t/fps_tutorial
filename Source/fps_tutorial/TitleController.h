// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitleController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShootEvent);

/**
 * 
 */
UCLASS()
class FPS_TUTORIAL_API ATitleController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintAssignable)
	FOnShootEvent OnShootEvent;


private:

	void OnShootInput();

protected:

	virtual void SetupInputComponent() override;

public:
	void BindToOnShootEvent(FOnShootEvent::FDelegate& InDelegate);
};
