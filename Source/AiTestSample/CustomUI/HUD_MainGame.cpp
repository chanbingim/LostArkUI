// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_MainGame.h"
#include "PlayerStateBarClass.h"

AHUD_MainGame::AHUD_MainGame()
{

}

void AHUD_MainGame::BeginPlay()
{
	Super::BeginPlay();
	 
	HUD_AddMainWidget(EWidgetName::WD_HPBar);
	HUD_AddMainWidget(EWidgetName::WD_SkillUI);
	HUD_AddMainWidget(EWidgetName::WD_Inventory);
}

void AHUD_MainGame::HUD_AddMainWidget(EWidgetName Name)
{
	TSubclassOf<class UUserWidget> TempWidgetClass = GetWidgetClass(Name); 
	UUserWidget* TempWidget = Find_Widget(Name);

	if (nullptr == TempWidget && !MainWidgetAry.Contains(TempWidget))
	{
		if (Name == EWidgetName::WD_HPBar || Name == EWidgetName::WD_SkillWidgetInFoUI)
		{
			TempWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), TempWidgetClass);
			MainWidgetAry.Add(TempWidget);
			TempWidget->AddToViewport();
		}
		else
		{
			UPlayerStateBarClass* MainWidget = Cast<UPlayerStateBarClass>(Find_Widget(EWidgetName::WD_HPBar));
			TempWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), TempWidgetClass);
			MainWidget->CanvasAddToWidget(TempWidget);
		}
	}
}

UUserWidget* AHUD_MainGame::Find_Widget(EWidgetName Name)
{
	for (auto var : MainWidgetAry)
	{
		if (var->GetClass() == GetWidgetClass(Name))
			return var;
	}

	return nullptr;
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

void AHUD_MainGame::HUD_RemoveWidget(EWidgetName Name)
{
	UUserWidget* CurrentWidget = Find_Widget(Name);

	if (nullptr != CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		MainWidgetAry.Remove(CurrentWidget);
	}
}
