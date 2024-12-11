// Fill out your copyright notice in the Description page of Project Settings.


#include "PopUpwidgetBase.h"
#include "HUD_MainGame.h"
#include "PlayerStateBarClass.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

FReply UPopUpwidgetBase::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	
	return reply.NativeReply;
}

FReply UPopUpwidgetBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	UpdatePopupZOrder();

	// Handled : 핸들을 반환하면 현재 위젯에서 이벤트 처리
	// Handled을 반환하면 마우스입력에 대한 처리가 위젯안에서만 일어남
	// 
	// UnHandled : 부모 위젯이 있다면 부모에서도 이벤트 처리
	// UnHandled을 반환하면 위젯안에서뿐만 아니라 위젯 밖의 이벤트도 처리된다.
	return FReply::Handled();
}

FReply UPopUpwidgetBase::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	UpdatePopupZOrder();

	// Handled : 핸들을 반환하면 현재 위젯에서 이벤트 처리
	// Handled을 반환하면 마우스입력에 대한 처리가 위젯안에서만 일어남
	// 
	// UnHandled : 부모 위젯이 있다면 부모에서도 이벤트 처리
	// UnHandled을 반환하면 위젯안에서뿐만 아니라 위젯 밖의 이벤트도 처리된다.
	return FReply::Handled();
}

void UPopUpwidgetBase::MoveWidget()
{
	if (GetVisibility() != ESlateVisibility::Visible)
		return;

	FVector2D StartPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	UpdatePopupZOrder();

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

void UPopUpwidgetBase::UpdatePopupZOrder()
{
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	if (OwningHUD)
		OwningHUD->UpdatePopUpWidgetZOrder(this);
}
