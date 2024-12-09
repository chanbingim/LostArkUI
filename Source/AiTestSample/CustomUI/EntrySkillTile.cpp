// Fill out your copyright notice in the Description page of Project Settings.


#include "EntrySkillTile.h"
#include "SlotBaseClass.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UEntrySkillTile::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CoolTimeText->SetVisibility(ESlateVisibility::Collapsed);
	KeynameText->SetVisibility(ESlateVisibility::Collapsed);
}

void UEntrySkillTile::NativeConstruct()
{
	Super::NativeConstruct();

}

void UEntrySkillTile::SetUIText(FString KeyName)
{
	KeynameText->SetText(FText::FromString(KeyName));
	KeynameText->SetVisibility(ESlateVisibility::Collapsed);
	CoolTimeText->SetVisibility(ESlateVisibility::Collapsed);
}

void UEntrySkillTile::CallCoolTime(FString cooltime)
{
	CoolTimeText->SetText(FText::FromString(cooltime));
	CoolTimeText->SetVisibility(ESlateVisibility::Collapsed);
	KeynameText->SetVisibility(ESlateVisibility::Collapsed);
}
