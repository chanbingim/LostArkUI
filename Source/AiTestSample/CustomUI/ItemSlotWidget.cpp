// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include "Components/Image.h"

void UItemSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SlotImage->SetVisibility(ESlateVisibility::Collapsed);
}

void UItemSlotWidget::NativeConstruct()
{
	Super:: NativeConstruct();
}
