// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

void UInventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemCount->SetVisibility(ESlateVisibility::Collapsed);
	SkillImage->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInventorySlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventorySlot* Invenslot = Cast<UInventorySlot>(ListItemObject);
	Type = Invenslot->Type;
	SlotIndex = Invenslot->SlotIndex;
	Count = Invenslot->Count;
	item_ID = Invenslot->item_ID;
	SkillImgaeTexture = Invenslot->SkillImgaeTexture;
	SetParentWidget(this);
	SetItemData();
}

void UInventorySlot::SetItemData()
{
	if (SkillImage == nullptr)
		return;

	SetWidgetImage(SkillImgaeTexture);

	if (Count <= 1)
		ItemCount->SetVisibility(ESlateVisibility::Collapsed);
	else
	{
		FString CountText = FString::FromInt(Count);
		ItemCount->SetText(FText::FromString(CountText));
		ItemCount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UInventorySlot::RemoveItemData()
{
	SkillImgaeTexture = nullptr;
	Count = 0;

	SetWidgetImage(SkillImgaeTexture);
	ItemCount->SetText(FText::FromString(""));
	ItemCount->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
