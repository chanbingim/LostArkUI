// Fill out your copyright notice in the Description page of Project Settings.


#include "FoldWidgetClass.h"
#include "TimerWidgetClass.h"
#include "HUD_MainGame.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"

void UFoldWidgetClass::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	FoldButton->OnClicked.AddDynamic(this, &UFoldWidgetClass::FoldWidget);
}

void UFoldWidgetClass::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

}

void UFoldWidgetClass::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{

}

void UFoldWidgetClass::NativeConstruct()
{
	Super::NativeConstruct();

	FoldWidget();
}

void UFoldWidgetClass::FoldWidget()
{
	if (bFoldState)
	{
		FoldButton->WidgetStyle.Normal.SetResourceObject(FoldTexture[0]); 
		FoldButton->WidgetStyle.Hovered.SetResourceObject(FoldTexture[0]);
		FoldButton->WidgetStyle.Pressed.SetResourceObject(FoldTexture[0]);

		for (auto var : HorizontalBox->GetAllChildren())
		{
			if (!ExceptWidget(var))
			{
				Current_WidgetWidth += Cast<UUserWidget>(var)->GetDesiredSize().X;
				var->SetVisibility(ESlateVisibility::Visible);
			}
		}
		bFoldState = false;
	}
	else
	{
		Current_WidgetWidth = Min_WidgetWidth;
		FoldButton->WidgetStyle.Normal.SetResourceObject(FoldTexture[1]);
		FoldButton->WidgetStyle.Hovered.SetResourceObject(FoldTexture[1]);
		FoldButton->WidgetStyle.Pressed.SetResourceObject(FoldTexture[1]);

		for (auto var : HorizontalBox->GetAllChildren())
		{
			if (!ExceptWidget(var))
			{
				var->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		bFoldState = true;
	}
	WidgetSize->SetWidthOverride(Current_WidgetWidth);
	Super::ForceLayoutPrepass();
}

bool UFoldWidgetClass::ExceptWidget(UWidget* widget)
{
	if (Cast<UTimerWidgetClass>(widget) || Cast<UButton>(widget))
	{
		return true;
	}
	return false;
}
