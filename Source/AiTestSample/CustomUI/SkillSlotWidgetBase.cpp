// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSlotWidgetBase.h"
#include "Components/TextBlock.h"

void USkillSlotWidgetBase::NativeOnInitialized()
{

}

void USkillSlotWidgetBase::NativeConstruct()
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
	SkillCoolTextBlock->SetVisibility(ESlateVisibility::Collapsed);
}
