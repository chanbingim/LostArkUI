// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillWidgetClass.h"
#include "HUD_MainGame.h"
#include "EntrySkillWidgetClass.h"
#include "Kismet/KismetStringLibrary.h"
#include "PlayerSkillDataClass.h"
#include "Components/Button.h"
#include "AiTestSample/PlayerDataSubSystem.h"
#include "Components/ListView.h"
#include "Components/SizeBox.h"
#include "PlayerStateBarClass.h"
#include "Kismet/GameplayStatics.h"
#include "../TestUISaveData.h"
#include "TriPodWidget.h"
#include "TriPodDataRow.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USkillWidgetClass::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ControllOption.Exit->OnClicked.AddDynamic(this, &USkillWidgetClass::RemoveSkillWidget);
	SkillPointDele.AddDynamic(this, &USkillWidgetClass::SetSkillPointText);
	ControllOption.ResetButton->OnClicked.AddDynamic(this, &USkillWidgetClass::ResetSkilLWidget);
	ControllOption.SaveButton->OnClicked.AddDynamic(this, &USkillWidgetClass::SaveSkillWidgetData);

	ControllOption.MoveButton->OnPressed.AddDynamic(this, &ThisClass::MoveWidget);
	ControllOption.MoveButton->OnReleased.AddDynamic(this, &ThisClass::StopMoveWidget);
}

void USkillWidgetClass::NativeConstruct()
{
	Super::NativeConstruct();

	auto playerData = GetGameInstance()->GetSubsystem<UPlayerDataSubSystem>();
	int32 SkillIndex = playerData->playerSkills.Num();

	if (SkillIndex == 0)
		GEngine->AddOnScreenDebugMessage(-3, 3.0f, FColor::Red, TEXT("Not Find Data"));

	for (int i = 0; i < SkillIndex; i++)
	{
		FArmorySkills skilldata = playerData->playerSkills[i];

		//FSkillData* SkillData = SkillDataTableComponent->FindRow<FSkillData>(FName(FString::FromInt(i + 1)), "");
		UEntrySkillWidgetClass* Temp = NewObject<UEntrySkillWidgetClass>(this, UEntrySkillWidgetClass::StaticClass());
		Temp->SetSkillName(skilldata.Name);
		Temp->SetSkillSock(skilldata.Type);
		Temp->SetSkillLevel(skilldata.Level);
		Temp->SetSkillImageURL(skilldata.Icon);
		Temp->SetSkillImage(playerData->skillImage[i]);

		/*Temp->SetSkillImage(SkillData->SkillImage);
		Temp->SetSkillName(SkillData->SkillName);
		Temp->SetSkillSock(SkillData->SkillSock);
		Temp->SetSkillData(SkillData->SkillDataInfo);
		Temp->SetTriPodData(SkillData->TriPodData);
		Temp->SetSKillCaption(SkillData->SkillCaption);*/

		AddSkillList(Temp);
	}
	
	SetSkillPointText();
	SetSkillTriPodText();
	SetVisibility(ESlateVisibility::Collapsed);
}

void USkillWidgetClass::SaveSkillWidgetData()
{
	// SpawnActor�� �ᱹ�� NewObject�� ����Ѵ�.
	UTestUISaveData* NewPlayerData = NewObject<UTestUISaveData>(); // ������ �÷��� ���п� Delete �Ƚᵵ ��.
	NewPlayerData->SaveWidget = this;

	if (false == UGameplayStatics::SaveGameToSlot(NewPlayerData, "SaveSlotName", 0))
	{

	}
}

void USkillWidgetClass::RemoveSkillWidget()
{
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());

	if (nullptr != OwningHUD)
	{
		OwningHUD->Find_Widget(EWidgetName::WD_SkillUI, EWidgetType::popUP)->SetVisibility(ESlateVisibility::Collapsed);
		RollBackList.Empty();
	}
}

void USkillWidgetClass::ResetSkilLWidget()
{
	TArray<UUserWidget *>SkillListWidget = ControllOption.SkillList->GetDisplayedEntryWidgets();

	for (auto var : SkillListWidget)
	{
		UEntrySkillWidgetClass* Temp = Cast<UEntrySkillWidgetClass>(var);
		Temp->ResetData();
	}

	Current_SkillPoint = MaxSkillPoint;
	SetSkillPointText();
}

void USkillWidgetClass::SetSkillTriPodText()
{
	FString TempText = FString::FromInt(Current_TriPodPoint).Append(" / ");
	TempText = TempText.Append(FString::FromInt(MaxTriPodPoint));

	ControllOption.TripodText->SetText(FText::FromString(TempText));
}

void USkillWidgetClass::SetSkillPointText()
{
	FString TempText = FString::FromInt(Current_SkillPoint).Append(" / ");
	TempText = TempText.Append(FString::FromInt(MaxSkillPoint));

	ControllOption.SkillPointText->SetText(FText::FromString(TempText));
}

void USkillWidgetClass::ItemClicked(UObject* obj)
{
	clickedItem = Cast<UEntrySkillWidgetClass>(obj);

	if (nullptr != clickedItem)
	{
		UDataTable* TriPodDataTable = clickedItem->GetTriPodData();
		int32 index = 0;

		if (TriPodDataTable == nullptr)
			return; 
		
		for (int count = 0; count < 8; count++)
		{
			FTriPodData* TriData = TriPodDataTable->FindRow<FTriPodData>(FName(FString::FromInt(count + 1)), "");
			UTriPodWidget* TriWidget = Cast<UTriPodWidget>(TriPodWidgetAry[count]);

			if (nullptr != TriWidget)
			{
				TriWidget->SetTriPodName(TriData->TriPodName);
				TriWidget->SetTriPodLevel(TriData->TriPodLevel);
				TriWidget->SetTriPodImage(TriData->TriPodImage);
				TriWidget->SetTriPodNum(count + 1);
				TriWidget->DataSetting();

				if (count == clickedItem->GetTriPodDataNum(index) - 1)
				{
					TriWidget->ControllOption.SelectImage->SetVisibility(ESlateVisibility::Visible);
					index += 1;
				}

			}
			else
				return;
		}

		clickedItem->UpdateTriPod();
	}
}

void USkillWidgetClass::AddSkillList(UObject* Item)
{
	ControllOption.SkillList->AddItem(Item);
}
