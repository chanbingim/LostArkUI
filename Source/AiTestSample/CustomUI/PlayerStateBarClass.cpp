// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBarClass.h"
#include "Widgets/Layout/Anchors.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "FoldWidgetClass.h"
#include "HUD_MainGame.h"
#include "SkillWidgetClass.h"
#include "Widget_HPbar.h"

void UPlayerStateBarClass::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UPlayerStateBarClass::NativeConstruct()
{
	Super::NativeConstruct();
	
}

UUserWidget* UPlayerStateBarClass::GetHPBar()
{
	for (auto i : ActiveWidget)
	{
		UWidget_HPbar* widgetCheck = Cast<UWidget_HPbar>(i);

		if (widgetCheck != nullptr)
			return i;
	}

	return nullptr;
}

USkillWidgetClass* UPlayerStateBarClass::GetSkillWidget()
{
	for (auto i : ActiveWidget)
	{
		auto* widgetCheck = Cast<USkillWidgetClass>(i);

		if (widgetCheck != nullptr)
			return widgetCheck;
	}

	return nullptr;
}

void UPlayerStateBarClass::CanvasAddToWidget(UUserWidget* newWidget)
{
	AHUD_MainGame* MainHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	int order = MainHUD->popUpWidgetAry.Num() + 10;
	if (nullptr != newWidget)
	{
		MainCanvas->AddChildToCanvas(newWidget);
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(newWidget->Slot);
		CanvasSlot->SetAutoSize(true);

		CanvasSlot->SetAnchors(FAnchors(0.5f,0.5f,0.5f,0.5f));
		CanvasSlot->SetPosition(FVector2D(0,0));
		CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		CanvasSlot->SetZOrder(order);

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black,
			FString::Printf (TEXT("oreder : %d"), CanvasSlot->GetZOrder()));

		MainHUD->popUpWidgetAry.Add(newWidget);
	}
}

void UPlayerStateBarClass::MoveSkillUI(FVector2D MousePos,TObjectPtr<UPanelSlot> _slot)
{
	AHUD_MainGame* MainHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	FVector2D WidgetPos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(_slot);
	CanvasSlot->SetPosition(WidgetPos - MousePos);
}
