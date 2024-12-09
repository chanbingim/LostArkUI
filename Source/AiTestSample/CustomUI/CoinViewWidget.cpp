// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinViewWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UCoinViewWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FDele_RSetting.AddDynamic(this, &UCoinViewWidget::SetReserves);
	SetCoinImage();
}

void UCoinViewWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UCoinViewWidget::SetReserves(int Data)
{
	Reserves = Data;
	WidgetText->SetText(FText::FromString(FString::FromInt(Reserves)));
}

void UCoinViewWidget::SetCoinImage()
{
	int index = -1;

	switch (tCoin)
	{
	case TypeCoin::shilling:
		index = 0;
		break;
	case TypeCoin::Gold:
		index = 1;
		break;
	case TypeCoin::Crystal:
		index = 2;
		break;
	}

	if (index < 0)
		return;

	WidgetImage->SetBrushFromTexture(CoinTexture[index]);
	WidgetImage->SetBrushFromTexture(CoinTexture[index]);
	WidgetImage->SetBrushFromTexture(CoinTexture[index]);
}