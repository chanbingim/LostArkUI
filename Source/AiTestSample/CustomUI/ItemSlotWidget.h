// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ItemSlotWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UItemSlotWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
	UImage* SlotImage = nullptr;
};
 