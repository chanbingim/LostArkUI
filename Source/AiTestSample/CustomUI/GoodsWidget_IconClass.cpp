// Fill out your copyright notice in the Description page of Project Settings.


#include "GoodsWidget_IconClass.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UGoodsWidget_IconClass::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	IconButton->OnClicked.AddDynamic(this, &UGoodsWidget_IconClass::WidgetClicked);
	WidgetImageSelect();
}

void UGoodsWidget_IconClass::NativeConstruct()
{
	Super::NativeConstruct();

	if (ArlamCount <= 0)
		VariableText->SetVisibility(ESlateVisibility::Collapsed);
}

void UGoodsWidget_IconClass::WidgetImageSelect()
{
	int index = -1;

	switch (tIcon)
	{
	case TypeIcon::Message:
		index = 0;
		break;
	case TypeIcon::LoaTalk:
		index = 1;
		break;
	case TypeIcon::CoinBox:
		index = 2;
		break;
	}

	if (index < 0)
		return;

	IconButton->WidgetStyle.Normal.SetResourceObject(IconImage[index]);
	IconButton->WidgetStyle.Hovered.SetResourceObject(IconImage[index]);
	IconButton->WidgetStyle.Pressed.SetResourceObject(IconImage[index]);
}

void UGoodsWidget_IconClass::WidgetClicked()
{
	
}
