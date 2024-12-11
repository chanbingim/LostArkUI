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
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent);
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	UFUNCTION()
	void MoveWidget();

	UFUNCTION()
	void StopMoveWidget();

	UFUNCTION()
	void UpdatePopupZOrder();

};
