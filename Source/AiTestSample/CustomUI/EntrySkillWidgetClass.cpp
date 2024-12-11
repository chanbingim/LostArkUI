// Fill out your copyright notice in the Description page of Project Settings.


#include "EntrySkillWidgetClass.h"
#include "SkillWidgetClass.h"
#include "HUD_MainGame.h"
#include "SkillDataRow.h"
#include "TriPodWidget.h"
#include "Kismet/KismetStringLibrary.h"
#include "TriPodDataRow.h"
#include "SlotBaseClass.h"
#include "SkillInfoUI_BaseClass.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UEntrySkillWidgetClass::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UpLevel->OnClicked.AddDynamic(this, &UEntrySkillWidgetClass::SkillLevelUPFUC);
	DownLevel->OnClicked.AddDynamic(this, &UEntrySkillWidgetClass::SkillLevelDOWNFUC);
	SkillLevel = 1;
	Nes_point = 1;
}

void UEntrySkillWidgetClass::NativeConstruct()
{
	Super::NativeConstruct();

	BackGroundWidget->SetWidgetSize(FVector2D(700,75));
}

void UEntrySkillWidgetClass::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UEntrySkillWidgetClass* SkillInfoUI = Cast<UEntrySkillWidgetClass>(ListItemObject);

	UIImage->SetBrushFromTexture(SkillInfoUI->SkillImage);
	SkillUIName->SetText(FText::FromString(SkillInfoUI->SkillName));
	SkillUISock->SetText(FText::FromString(SkillInfoUI->SkillSock));

	SkillCaption = SkillInfoUI->SkillCaption;
	SkillImage = SkillInfoUI->SkillImage;
	SkillName = SkillInfoUI->SkillName;
	SkillSock = SkillInfoUI->SkillSock;
	DataComponent = SkillInfoUI->DataComponent;
	TriPodDataComponent = SkillInfoUI->TriPodDataComponent;
	BackGroundWidget->SkillImgaeTexture = SkillInfoUI->SkillImage;
	BackGroundWidget->SetParentWidget(this);

	for(int i = 0; i <3; i++)
		TriPodInfo[i] = -1;

	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	USkillWidgetClass* CurrentWidget = Cast<USkillWidgetClass>(OwningHUD->Find_Widget(EWidgetName::WD_SkillUI, EWidgetType::popUP));
	if (CurrentWidget->clickedItem == nullptr)
	{
		CurrentWidget->ItemClicked(this);
	}
	UpdateTriPod();
}


void UEntrySkillWidgetClass::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	ViewSkillInfo();
}

void UEntrySkillWidgetClass::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	HiddenSkillInfo();
}

FReply UEntrySkillWidgetClass::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true ||
		InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
	{
		AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
		USkillWidgetClass* CurrentWidget = Cast<USkillWidgetClass>(OwningHUD->Find_Widget(EWidgetName::WD_SkillUI, EWidgetType::popUP));
		if (CurrentWidget->clickedItem == nullptr)
		{
			CurrentWidget->ItemClicked(this);
		}
	}

	return reply.NativeReply;
}

void UEntrySkillWidgetClass::SkillLevelUPFUC()
{
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	USkillWidgetClass* CurrentWidget = Cast<USkillWidgetClass>(OwningHUD->Find_Widget(EWidgetName::WD_SkillUI, EWidgetType::popUP));
	
	if (SkillLevel >= 12)
		return;

	if (CurrentWidget->Current_SkillPoint >= Nes_point)
	{
		CurrentWidget->Current_SkillPoint -= Nes_point;
		SkillLevel += 1;

		CurrentWidget->SkillPointDele.Broadcast();
		SettingData();
	}
}

void UEntrySkillWidgetClass::SkillLevelDOWNFUC()
{
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	USkillWidgetClass* CurrentWidget = Cast<USkillWidgetClass>(OwningHUD->Find_Widget(EWidgetName::WD_SkillUI, EWidgetType::popUP));
	FSkillInfoData* Data = DataComponent->FindRow<FSkillInfoData>(FName(FString::FromInt(SkillLevel - 1)), "");

	if (SkillLevel > 1)
	{
		CurrentWidget->Current_SkillPoint += Data->Ne_Point;
		SkillLevel -= 1;

		CurrentWidget->SkillPointDele.Broadcast();
		UpdateTriPod();
		SettingData();
	}
}

void UEntrySkillWidgetClass::UpdateTriPod()
{
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	USkillWidgetClass* CurrentWidget = Cast<USkillWidgetClass>(OwningHUD->Find_Widget(EWidgetName::WD_SkillUI, EWidgetType::popUP));

	int TriPodindex = SkillLevel * 0.3;
	for (auto var : CurrentWidget->TriPodWidgetAry)
	{
		UTriPodWidget* TriPod = Cast<UTriPodWidget>(var);

		if (TriPodindex > TriPod->GetTriPodNum() * 0.3)
		{
			if (TriPodInfo[TriPodindex - 1] == TriPod->GetTriPodNum())
			{
				TriPod->ControllOption.SelectImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			continue;
		}
		else
		{
			TriPod->ControllOption.SelectImage->SetVisibility(ESlateVisibility::Collapsed);
			TriPodInfo[TriPodindex] = -1;
		}
	}
}

void UEntrySkillWidgetClass::SettingData()
{
	//데이블 데이터 참조후 설정
	FString TempText = FString::FromInt(SkillLevel);
	SkillUIlLevel->SetText(FText::FromString(TempText));

	if (DataComponent == nullptr)
		return;

	FSkillInfoData* Data = DataComponent->FindRow<FSkillInfoData>(FName(FString::FromInt(SkillLevel)), "");
	if (SkillLevel < 12)
	{
		Nes_point = Data->Ne_Point;
		SkillUIPoint->SetText(FText::FromString(FString::FromInt(Data->Ne_Point)));
		SkillUIPointText->SetText(FText::FromString(TEXT("필요포인트")));

		int Imagenum = SkillLevel * 0.3;

		if(TriPodImageAry[Imagenum] != nullptr)
			TripodImage->SetBrushFromTexture(TriPodImageAry[Imagenum]);
	}
	else
	{
		Nes_point = Data->Ne_Point;
		SkillUIPoint->SetText(FText::FromString(TEXT("")));
		SkillUIPointText->SetText(FText::FromString(TEXT("최고레벨")));
	}
}

void UEntrySkillWidgetClass::SetWidgetData(UUserWidget* SettingData)
{
	USkillInfoUI_BaseClass* SettingWidget = Cast<USkillInfoUI_BaseClass>(SettingData);
	FSkillInfoData* Data = DataComponent->FindRow<FSkillInfoData>(FName(FString::FromInt(SkillLevel)), "");
	FTriPodData* TriData1 = TriPodDataComponent->FindRow<FTriPodData>(FName(FString::FromInt(TriPodInfo[0])), "");
	FTriPodData* TriData2 = TriPodDataComponent->FindRow<FTriPodData>(FName(FString::FromInt(TriPodInfo[1])), "");
	FTriPodData* TriData3 = TriPodDataComponent->FindRow<FTriPodData>(FName(FString::FromInt(TriPodInfo[2])), "");

	SettingWidget->Name = SkillName;
	SettingWidget->Image = SkillImage;
	SettingWidget->Sock = SkillSock;
	SettingWidget->Level = SkillLevel;
	SettingWidget->Caption = SkillCaption;
	SettingWidget->CoolTime = Data->CoolTime;
	SettingWidget->Dmage = Data->SkillDamage;
	SettingWidget->SKillCost = Data->SKillCost;
	SettingWidget->Info = Data->SkillInfoText;
	SettingWidget->Partdestruction = Data->Partdestruction;
	SettingWidget->neutralize = Data->neutralize;
	SettingWidget->SuperArmer = Data->SuperArmer;

	if (TriData1 != nullptr)
	{
		SettingWidget->TriPodImage.Add(TriData1->TriPodImage);
		SettingWidget->TriPodName.Add(TriData1->TriPodName);
		SettingWidget->TriPodLevel.Add(TriData1->TriPodLevel);
		SettingWidget->TriPodInfo.Add(TriData1->TriPodInfo);
	}

	if (TriData2 != nullptr)
	{
		SettingWidget->TriPodImage.Add(TriData2->TriPodImage);
		SettingWidget->TriPodName.Add(TriData2->TriPodName);
		SettingWidget->TriPodLevel.Add(TriData2->TriPodLevel);
		SettingWidget->TriPodInfo.Add(TriData2->TriPodInfo);
	}

	if (TriData3 != nullptr)
	{
		SettingWidget->TriPodImage.Add(TriData3->TriPodImage);
		SettingWidget->TriPodName.Add(TriData3->TriPodName);
		SettingWidget->TriPodLevel.Add(TriData3->TriPodLevel);
		SettingWidget->TriPodInfo.Add(TriData3->TriPodInfo);
	}

	SettingWidget->SettingData();
}

void UEntrySkillWidgetClass::ViewSkillInfo()
{
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());

	OwningHUD->HUD_AddMainWidget(EWidgetName::WD_SkillWidgetInFoUI, EWidgetType::mainWD);
	UUserWidget* InfoWidget = OwningHUD->Find_Widget(EWidgetName::WD_SkillWidgetInFoUI, EWidgetType::mainWD);
	if (nullptr == InfoWidget)
		return;

	SetWidgetData(InfoWidget);

	FGeometry geometry = UWidgetLayoutLibrary::GetViewportWidgetGeometry(this);
	FVector2D Pos = geometry.AbsoluteToLocal(this->GetCachedGeometry().GetAbsolutePosition()) +
		this->GetCachedGeometry().GetLocalSize() * 0.7;

	int viewPortX, viewPortY;
	GetOwningPlayer()->GetViewportSize(viewPortX, viewPortY);
		float WidgetPosY = viewPortY - 430;

	InfoWidget->SetPositionInViewport(FVector2D(Pos.X, WidgetPosY));
}

void UEntrySkillWidgetClass::HiddenSkillInfo()
{
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	OwningHUD->HUD_RemoveWidget(EWidgetName::WD_SkillWidgetInFoUI, EWidgetType::mainWD);
}

void UEntrySkillWidgetClass::SelectWidget()
{
	AHUD_MainGame* OwningHUD = Cast<AHUD_MainGame>(GetOwningPlayer()->GetHUD());
	UUserWidget* InfoWidget = OwningHUD->Find_Widget(EWidgetName::WD_SkillWidgetInFoUI, EWidgetType::mainWD);
	USkillWidgetClass* SkillUI = Cast<USkillWidgetClass>(InfoWidget);

	SkillUI->ItemClicked(this);
}


void UEntrySkillWidgetClass::ResetData()
{
	SkillUIlLevel->SetText(FText::FromString(TEXT("1")));
	SkillUIPoint->SetText(FText::FromString(TEXT("1")));
	SkillUIPointText->SetText(FText::FromString(TEXT("필요포인트")));
	TripodImage->SetBrushFromTexture(TriPodImageAry[0]);
	UpdateTriPod();

	Nes_point = 1;
	SkillLevel = 1;
}
