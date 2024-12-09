// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_HPbar.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/AiTestSampleCharacter.h"
#include "Kismet/KismetStringLibrary.h"
#include "Components/TileView.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidget_HPbar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Dele_HPSetting.AddDynamic(this, &UWidget_HPbar::SetHpState);
	Dele_MPSetting.AddDynamic(this, &UWidget_HPbar::SetMpState);
}

void UWidget_HPbar::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
}

void UWidget_HPbar::SetHpState(float CurrentHP, float MaxHP)
{
	PlayerStateUI.HPBar->SetPercent( CurrentHP / MaxHP);
	FString TempText = FString::SanitizeFloat(CurrentHP).Append(" / ");
	TempText = TempText.Append(FString::SanitizeFloat(MaxHP));

	PlayerStateUI.HPTextBlock->SetText(FText::FromString(TempText));
}

void UWidget_HPbar::SetMpState(float CurrentMP, float MaxMP)
{
	PlayerStateUI.MPBar->SetPercent( CurrentMP / MaxMP );
	FString TempText = FString::SanitizeFloat(CurrentMP).Append(" / ");
	TempText = TempText.Append(FString::SanitizeFloat(MaxMP));

	PlayerStateUI.MPTextBlock->SetText(FText::FromString(TempText));
}
