// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpwidgetBase.h"
#include "SkillWidgetClass.generated.h"

class UButton;
class UCanvasPanel;
class UTextBlock;
class UListView;
class USizeBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDele_SkillPointSetting);
 
USTRUCT(BlueprintType)
struct FSkillUIOption
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USizeBox* WidgetSize = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* EditSkillPageName = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* MoveButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* PageName = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillPointText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TripodText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* Exit = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* ResetButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* LoadSkillTree = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* SaveButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* BackButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UListView* SkillList = nullptr;
};

UCLASS()
class AITESTSAMPLE_API USkillWidgetClass : public UPopUpwidgetBase
{
	GENERATED_BODY()
private :
	TArray<UObject*> RollBackList;

	UPROPERTY(EditAnywhere, Category = "SkillPoint")
	int32 MaxSkillPoint = 407;
	
	UPROPERTY(EditAnywhere, Category = "SkillPoint")
	int32 MaxTriPodPoint = 18;

protected :
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

	UPROPERTY(EditAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* SkillDataTableComponent = nullptr;
public :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Select")
	class UEntrySkillWidgetClass* clickedItem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TirPod")
	TArray<UUserWidget*> TriPodWidgetAry;

	UFUNCTION()
	void SaveSkillWidgetData();
	
	UFUNCTION()
	void RemoveSkillWidget();

	UFUNCTION()
	void ResetSkilLWidget();

	UFUNCTION()
	void SetSkillTriPodText();

	UFUNCTION()
	void SetSkillPointText();

	UFUNCTION()
	void ItemClicked(UObject* obj);

	UFUNCTION()
	void AddSkillList(UObject* Item);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillPoint")
	int Current_SkillPoint = 407;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillPoint")
	int Current_TriPodPoint = 18;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillUIOption ControllOption;

	FDele_SkillPointSetting SkillPointDele;
};
