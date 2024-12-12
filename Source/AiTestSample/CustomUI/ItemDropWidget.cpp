// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDropWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"

void UItemDropWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UItemDropWidget::NativeConstruct()
{
	Super::NativeConstruct();

	okayButton->OnClicked.AddUniqueDynamic(this, &ThisClass::DropItemEvent);
	cancelButton->OnClicked.AddUniqueDynamic(this, &ThisClass::CancelDropItemEvent);
}

void UItemDropWidget::DropItemEvent()
{
	backgroundBlur->SetBlurStrength(0.0f);
	SetVisibility(ESlateVisibility::Collapsed);
}

void UItemDropWidget::CancelDropItemEvent()
{
	backgroundBlur->SetBlurStrength(0.0f);
	SetVisibility(ESlateVisibility::Collapsed);
}

void UItemDropWidget::ItemDropWidgetOnActive()
{
	backgroundBlur->SetBlurStrength(20.0f);
	SetVisibility(ESlateVisibility::Visible);
}
