// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDropWidget.generated.h"


class UButton;
class UBackgroundBlur;

UCLASS()
class AITESTSAMPLE_API UItemDropWidget : public UUserWidget
{
	GENERATED_BODY()

protected :
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

public :
	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* backgroundBlur = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* okayButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* cancelButton = nullptr;

	UFUNCTION()
	void DropItemEvent();

	UFUNCTION()
	void CancelDropItemEvent();

	UFUNCTION()
	void ItemDropWidgetOnActive();
};
