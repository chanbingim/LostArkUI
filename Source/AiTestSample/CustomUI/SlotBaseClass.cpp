// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotBaseClass.h"
#include "HUD_MainGame.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InventorySlot.h"
#include "InventroyUIClass.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SkillWidgetClass.h"
#include "SkillWidgetDragAndDrop.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"

void USlotBaseClass::NativeConstruct()
{
	Super::NativeConstruct();

}

void USlotBaseClass::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

FReply USlotBaseClass::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
	{
		if (SkillImgaeTexture != nullptr)
		{
			DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
			AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
			if (Type == FSlotType::UIType)
			{
				USkillWidgetClass* CurrentWidget = Cast<USkillWidgetClass>(OwningHUD->Find_Widget(EWidgetName::WD_SkillUI));
				if (CurrentWidget != nullptr)
					CurrentWidget->ItemClicked(ParentWidget);
			}
			
			reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		}
	}
	
	return reply.NativeReply;
}

void USlotBaseClass::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	USkillWidgetDragAndDrop* slot = Cast<USkillWidgetDragAndDrop>(InOperation);
	USlotBaseClass* selectSlot = Cast<USlotBaseClass>(slot->selectWidget);

	if (selectSlot->Type == FSlotType::ItemSlotType)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("DragCancel"));
	}
		
}

void USlotBaseClass::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (SkillImgaeTexture == nullptr)
		return;

	if (OutOperation == nullptr)
	{
		USkillWidgetDragAndDrop* DragWidget = NewObject<USkillWidgetDragAndDrop>();
		OutOperation = DragWidget;
		DragWidget->selectWidget = this;

		if (DragWidgetClass != nullptr)
		{
			USlotBaseClass* slot = CreateWidget<USlotBaseClass>(GetOwningPlayer(), DragWidgetClass);
			slot->SetRenderTranslation(DragOffset);
			slot->SetWidgetImage(SkillImgaeTexture);
			DragWidget->DefaultDragVisual = slot;
			DragWidget->Pivot = EDragPivot::MouseDown;
		}
	}
}

bool USlotBaseClass::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USkillWidgetDragAndDrop* slot = Cast<USkillWidgetDragAndDrop>(InOperation);
	if (nullptr != slot)
	{
		//drop func Call To Slot Widget
		//From slot : Inopeartion->Selectwidget
		//To slot : this
		USlotBaseClass* fromSlot = Cast<USlotBaseClass>(slot->selectWidget);

		if (Type == FSlotType::SkillType && fromSlot->Type == FSlotType::UIType)
		{
			SkillImgaeTexture = fromSlot->SkillImgaeTexture;
			SetWidgetImage(fromSlot->SkillImgaeTexture);
		}

		if (fromSlot->Type == FSlotType::ItemSlotType && this->Type == FSlotType::ItemSlotType)
		{
			AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
			UInventroyUIClass* CurrentWidget = Cast<UInventroyUIClass>(OwningHUD->Find_Widget(EWidgetName::WD_Inventory));	
			CurrentWidget->UIRefesh(fromSlot, this);
		}
		
		return true;
	}
	else
		return false;

	
}

void USlotBaseClass::SetWidgetImage(UTexture2D* texture)
{
	SkillImage->SetBrushFromTexture(texture);
	if(texture != nullptr)
		SkillImage->SetVisibility(ESlateVisibility::Visible);
	else
		SkillImage->SetVisibility(ESlateVisibility::Collapsed);
}

void USlotBaseClass::SetWidgetSize(FVector2D size)
{
	WidgetSize->SetWidthOverride(size.X);
	WidgetSize->SetHeightOverride(size.Y);
}
