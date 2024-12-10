// Fill out your copyright notice in the Description page of Project Settings.


#include "PopUpwidgetBase.h"
#include "HUD_MainGame.h"
#include "PlayerStateBarClass.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UPopUpwidgetBase::MoveWidget()
{
	if (GetVisibility() != ESlateVisibility::Visible)
		return;

	FVector2D StartPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
	MousePos = StartPos - CanvasSlot->GetPosition();

	GetWorld()->GetTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateLambda(
		[this]()
		{
			AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
			UPlayerStateBarClass* MainWidget = Cast<UPlayerStateBarClass>(OwningHUD->Find_Widget(EWidgetName::WD_HPBar, EWidgetType::mainWD));
			MainWidget->MoveSkillUI(MousePos, Slot);
		}
	), 0.1f, true);
}

void UPopUpwidgetBase::StopMoveWidget()
{
	GetWorld()->GetTimerManager().ClearTimer(timerHandle);
}

void UPopUpwidgetBase::UpdatePopUpWidgetOrder()
{

}