// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidgetClass.generated.h"

class UTextBlock;
class USizeBox;

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UTimerWidgetClass : public UUserWidget
{
	GENERATED_BODY()
private :
	time_t localTime;
	struct tm* pLocal = nullptr;

protected :
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	USizeBox* WidgetSize = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WidgetText = nullptr;
};
