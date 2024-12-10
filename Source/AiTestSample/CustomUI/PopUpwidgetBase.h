// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopUpwidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UPopUpwidgetBase : public UUserWidget
{
	GENERATED_BODY()

	FVector2D MousePos;
	FTimerHandle timerHandle;

protected :
	UFUNCTION()
	void MoveWidget();

	UFUNCTION()
	void StopMoveWidget();

public :
	UFUNCTION()
	void UpdatePopUpWidgetOrder();
};
