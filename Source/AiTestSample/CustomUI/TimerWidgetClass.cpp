// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWidgetClass.h"
#include "Kismet/KismetStringLibrary.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include <ctime>

void UTimerWidgetClass::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	
}

void UTimerWidgetClass::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTimerWidgetClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	localTime = time(NULL);
	pLocal = localtime(&localTime);

	char buffer[126];
	strftime(buffer, sizeof(buffer), "%H:%M", pLocal);
	WidgetText->SetText(FText::FromString(buffer));
}
