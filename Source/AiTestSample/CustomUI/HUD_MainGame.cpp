// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_MainGame.h"
#include "PlayerStateBarClass.h"
#include "Components/CanvasPanelSlot.h"

AHUD_MainGame::AHUD_MainGame()
{

}

void AHUD_MainGame::BeginPlay()
{
	Super::BeginPlay();
	
	HUD_AddMainWidget(EWidgetName::WD_HPBar, EWidgetType::mainWD);
	HUD_AddMainWidget(EWidgetName::WD_SkillUI, EWidgetType::popUP);
	HUD_AddMainWidget(EWidgetName::WD_Inventory, EWidgetType::popUP);
}

void AHUD_MainGame::HUD_AddMainWidget(EWidgetName Name,const EWidgetType& findType)
{
	TSubclassOf<class UUserWidget> TempWidgetClass = GetWidgetClass(Name); 
	UUserWidget* TempWidget = Find_Widget(Name, findType);

	if (nullptr == TempWidget && !MainWidgetAry.Contains(TempWidget))
	{
		if (Name == EWidgetName::WD_HPBar || Name == EWidgetName::WD_SkillWidgetInFoUI)
		{
			TempWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), TempWidgetClass);
			MainWidgetAry.Add(TempWidget);
			TempWidget->AddToViewport(0);
		}
		else
		{
			UPlayerStateBarClass* MainWidget = Cast<UPlayerStateBarClass>(Find_Widget(EWidgetName::WD_HPBar, EWidgetType::mainWD));
			TempWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), TempWidgetClass);
			MainWidget->CanvasAddToWidget(TempWidget);
		}
	}
}

UUserWidget* AHUD_MainGame::Find_Widget(EWidgetName Name, const EWidgetType& findType)
{
	TArray<UUserWidget*> tempWidget;
	switch (findType)
	{
	case EWidgetType::popUP :
		tempWidget = popUpWidgetAry;
		break;
	case EWidgetType::mainWD :
		tempWidget = MainWidgetAry;
		break;
	}
	
	for (auto var : tempWidget)
	{
		if (var->GetClass() == GetWidgetClass(Name))
			return var;
	}

	return nullptr;
}

void AHUD_MainGame::UpdatePopUpWidgetZOrder(UUserWidget* clickwidget)
{
	if (popUpWidgetAry.Num() > 0)
	{
		if (popUpWidgetAry.Last() == clickwidget)
			return;

		popUpWidgetAry.Remove(clickwidget);
		popUpWidgetAry.Add(clickwidget);
	}

	int32 orderIndex = 10;
	for (auto widgetElement : popUpWidgetAry)
	{
		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(widgetElement->Slot);
		CanvasSlot->SetZOrder(orderIndex);
		orderIndex++;
	}
}

TSubclassOf<class UUserWidget> AHUD_MainGame::GetWidgetClass(const EWidgetName Name)
{
	switch (Name)
	{
	case EWidgetName::WD_HPBar :
		return WD_HPBarClass;
	case EWidgetName::WD_SkillUI:
		return WD_SkillUI;
	case EWidgetName::WD_SkillWidgetInFoUI :
		return WD_SkillWidgetInFoUI;
	case EWidgetName::WD_Inventory:
		return WD_InventroyWidget;
	}

	return nullptr;
}

void AHUD_MainGame::HUD_RemoveWidget(EWidgetName Name,const EWidgetType& findType)
{
	UUserWidget* CurrentWidget = Find_Widget(Name, findType);

	if (nullptr != CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		MainWidgetAry.Remove(CurrentWidget);
	}
}
