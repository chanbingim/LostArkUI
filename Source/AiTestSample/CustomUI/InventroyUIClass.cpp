// Fill out your copyright notice in the Description page of Project Settings.


#include "InventroyUIClass.h"
#include "HUD_MainGame.h"
#include "PlayerStateBarClass.h"
#include "InventorySlot.h"
#include "Components/Button.h"
#include "Components/TileView.h"
#include "ItemDropWidget.h"

void UInventroyUIClass::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InvenOption.ExitButton->OnClicked.AddDynamic(this, &UInventroyUIClass::CloseWidget);

	InvenOption.MoveWidgetButton->OnPressed.AddDynamic(this, &ThisClass::MoveWidget);
	InvenOption.MoveWidgetButton->OnReleased.AddDynamic(this, &ThisClass::StopMoveWidget);
	InvenOption.tileView->OnItemClicked().AddUObject(this, &ThisClass::HandleTileViewItemClicked);
	InvenOption.dropItemDWidget->okayButton->OnClicked.AddUniqueDynamic(this, &ThisClass::breakItemEvent);
}

void UInventroyUIClass::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 80; i++)
	{
		UInventorySlot* InvenSlot = NewObject<UInventorySlot>(this, UInventorySlot::StaticClass());
		InvenSlot->item_ID = 0;
		InvenSlot->SlotIndex = i;
		InvenSlot->Type = FSlotType::ItemSlotType;
		InvenSlot->SkillImgaeTexture = nullptr;
		InvenOption.tileView->AddItem(InvenSlot);
	}
	SetVisibility(ESlateVisibility::Collapsed);
}

void UInventroyUIClass::HandleTileViewItemClicked(UObject* ClickedItem)
{
	UpdatePopupZOrder();
}

void UInventroyUIClass::CloseWidget()
{
	if (GetVisibility() == ESlateVisibility::Visible)
		SetVisibility(ESlateVisibility::Collapsed);
}

void UInventroyUIClass::ItemSetting()
{
	UInventorySlot* FristSlot = Cast<UInventorySlot>(InvenOption.tileView->GetItemAt(0));
	FristSlot->SkillImgaeTexture = ItemTexture[0];
	FristSlot->item_ID = 1;
	FristSlot->Count = 2;
	
	FristSlot = Cast<UInventorySlot>(InvenOption.tileView->GetItemAt(1));
	FristSlot->SkillImgaeTexture = ItemTexture[1];
	FristSlot->item_ID = 1;
	FristSlot->Count = 1;

	//listview and tileview update
	InvenOption.tileView->RegenerateAllEntries();
}

void UInventroyUIClass::UIRefesh(UObject* FromWidget,UObject* ToWidget)
{
	UInventorySlot* fSlot = Cast<UInventorySlot>(FromWidget);
	UInventorySlot* toSlot = Cast<UInventorySlot>(ToWidget);

	UInventorySlot* temp = NewObject<UInventorySlot>();
	temp->SkillImgaeTexture = fSlot->SkillImgaeTexture;
	temp->Count = fSlot->Count;
	temp->item_ID = fSlot->item_ID;

	fSlot->SkillImgaeTexture = toSlot->SkillImgaeTexture;
	fSlot->Count = toSlot->Count;
	fSlot->item_ID = toSlot->item_ID;

	toSlot->SkillImgaeTexture = temp->SkillImgaeTexture;
	toSlot->Count = temp->Count;
	toSlot->item_ID = temp->item_ID;

	fSlot->SetItemData();
	toSlot->SetItemData();
}

void UInventroyUIClass::dropItemWidgetShowEvent(UObject* selectSlot)
{
	selectSlotItem = selectSlot;
	InvenOption.dropItemDWidget->ItemDropWidgetOnActive();
}

void UInventroyUIClass::breakItemEvent()
{
	UInventorySlot* slotInfo = Cast<UInventorySlot>(selectSlotItem);

	if (slotInfo)
	{
		slotInfo->RemoveItemData();
	}
}
