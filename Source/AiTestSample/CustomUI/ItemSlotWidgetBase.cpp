// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidgetBase.h"
#include "Components/TextBlock.h"

void UItemSlotWidgetBase::NativeOnInitialized()
{

}

void UItemSlotWidgetBase::NativeConstruct()
{
	if (SlotNameText != "")
	{
		SlotTextBlock->SetText(FText::FromString(SlotNameText));
		SlotTextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		SlotTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}

	SetWidgetImage(SkillImgaeTexture);
}
