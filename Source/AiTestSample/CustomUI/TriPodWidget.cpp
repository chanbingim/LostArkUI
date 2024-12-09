// Fill out your copyright notice in the Description page of Project Settings.


#include "TriPodWidget.h"
#include "SkillWidgetClass.h"
#include "EntrySkillWidgetClass.h"
#include "HUD_MainGame.h"
#include "SkillWidgetClass.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UTriPodWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ControllOption.LevelButton->OnClicked.AddDynamic(this, &UTriPodWidget::TriPodSelect);
	ControllOption.ImageButton->OnClicked.AddDynamic(this, &UTriPodWidget::TriPodSelect);

	ControllOption.SelectImage->SetVisibility(ESlateVisibility::Collapsed);
}

void UTriPodWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	USkillWidgetClass* CurrentWidget = Cast<USkillWidgetClass>(OwningHUD->Find_Widget(EWidgetName::WD_SkillUI));

	if(CurrentWidget != nullptr)
		CurrentWidget->TriPodWidgetAry.Add(this);
}

void UTriPodWidget::TriPodSelect()
{
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	USkillWidgetClass* CurrentWidget = Cast<USkillWidgetClass>(OwningHUD->Find_Widget(EWidgetName::WD_SkillUI));
	UEntrySkillWidgetClass* BasetWidget = CurrentWidget->clickedItem;
	
	
	int index = TriPodNum * 0.3;
	if (BasetWidget->GetSkillLevel() * 0.3 < index + 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString("Unable"));
		return;
	}
		
	for (auto var : CurrentWidget->TriPodWidgetAry)
	{
		UTriPodWidget* CurrentSelectWidget = Cast<UTriPodWidget>(var);
		int current_index = CurrentSelectWidget->TriPodNum * 0.3;
		if (CurrentSelectWidget->ControllOption.SelectImage->GetVisibility() == ESlateVisibility::SelfHitTestInvisible && index == current_index)
		{
			CurrentWidget->Current_TriPodPoint += 1;
			CurrentSelectWidget->ControllOption.SelectImage->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
			continue;
	}

	CurrentWidget->Current_TriPodPoint -= 1;
	CurrentWidget->SetSkillTriPodText();
	BasetWidget->SetTriPodDataNum(index, TriPodNum);
	ControllOption.SelectImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UTriPodWidget::DataSetting()
{
	ControllOption.TripodImage->SetBrushFromTexture(TriImage);
	ControllOption.TripodName->SetText(FText::FromString(TriPodName));
}
