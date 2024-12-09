// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillInfoUI_BaseClass.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USkillInfoUI_BaseClass::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void USkillInfoUI_BaseClass::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillInfoUI_BaseClass::SettingData()
{
	BaseOption.SkillNameText->SetText(FText::FromString(Name));
	BaseOption.SkillImage->SetBrushFromTexture(Image);
	BaseOption.SkillSockText->SetText(FText::FromString(Sock));
	BaseOption.SkillCaptionText->SetText(FText::FromString(Caption));

	FString TempText;
	TempText = L"재사용 대기시간 ";
	TempText = TempText.Append(FString::FromInt(CoolTime));
	TempText = TempText.Append(L"초");
	BaseOption.SkillCoolTimeText->SetText(FText::FromString(TempText));

	TempText = L"스킬 레벨 ";
	TempText = TempText.Append(FString::FromInt(Level));
	BaseOption.SkillLevelText->SetText(FText::FromString(TempText));

	TempText = FString(L"소모 마나 ").Append(FString::FromInt(SKillCost).Append(L" 소모"));
	BaseOption.SkillMaNaTimeText->SetText(FText::FromString(TempText));

	BaseOption.SkillInfoText->SetText(FText::FromString(Info));

	if (Partdestruction > 0)
	{
		TempText = L"부위파괴 : 레벨 ";
		TempText = TempText.Append(FString::FromInt(Partdestruction));
		BaseOption.SkillPartdestructionText->SetText(FText::FromString(TempText));
	}
	else
		BaseOption.SkillPartdestructionText->SetVisibility(ESlateVisibility::Hidden);

	if (neutralize > 0)
	{
		TempText = L"무력화 : ";

		switch (neutralize)
		{
		case 1:
			TempText = TempText.Append(L"하");
			break;

		case 2 :
			TempText = TempText.Append(L"중");
			break;

		case 3 :
			TempText = TempText.Append(L"중상");
			break;

		case 4 :
			TempText = TempText.Append(L"상");
			break;

		case 5 :
			TempText = TempText.Append(L"최상");
			break;
		}
		BaseOption.SkillneutralizeText->SetText(FText::FromString(TempText));
	}
	else
		BaseOption.SkillneutralizeText->SetVisibility(ESlateVisibility::Hidden);

	if (Partdestruction > 0)
	{
		TempText = "슈퍼아머 : ";
		BaseOption.SkillSuperArmerText->SetText(FText::FromString(TempText));
	}
	else
		BaseOption.SkillSuperArmerText->SetVisibility(ESlateVisibility::Hidden);

	if (TriPodImage.Num() <= 0)
		return;

	BaseOption.SkillTriPodFristImage->SetBrushFromTexture(TriPodImage[0]);
	BaseOption.SkillTriPodFristName->SetText(FText::FromString(TriPodName[0]));
	BaseOption.SkillTriPodFristLevelText->SetText(FText::FromString(FString("LV ").Append(FString::FromInt(TriPodLevel[0]))));
	BaseOption.SkillTriPodFristInfoText->SetText(FText::FromString(TriPodInfo[0]));

	if (TriPodImage.Num() <= 1)
		return;

	BaseOption.SkillTriPodSecondImage->SetBrushFromTexture(TriPodImage[1]);
	BaseOption.SkillTriPodSecondNameText->SetText(FText::FromString(TriPodName[1]));
	BaseOption.SkillTriPodSecondLevelText->SetText(FText::FromString(FString("LV ").Append(FString::FromInt(TriPodLevel[1]))));
	BaseOption.SkillTriPodSecondInfoText->SetText(FText::FromString(TriPodInfo[1]));

	if (TriPodImage.Num() <= 2)
		return;

	BaseOption.SkillTriPodThreeImage->SetBrushFromTexture(TriPodImage[2]);
	BaseOption.SkillTriPodThreeNameText->SetText(FText::FromString(TriPodName[2]));
	BaseOption.SkillTriPodThreeLevelText->SetText(FText::FromString(FString("LV ").Append(FString::FromInt(TriPodLevel[2]))));
	BaseOption.SkillTriPodThreeInfoText->SetText(FText::FromString(TriPodInfo[2]));
}
