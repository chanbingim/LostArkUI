// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "EntrySkillWidgetClass.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AITESTSAMPLE_API UEntrySkillWidgetClass : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private :
	UPROPERTY(VisibleAnywhere, Category = "info")
	int32 Nes_point;

	UPROPERTY(VisibleAnywhere, Category = "info")
	int32 SkillLevel;

	UPROPERTY(VisibleAnywhere, Category = "info")
	FString SkillCaption = "";

	UPROPERTY(VisibleAnywhere, Category = "info")
	FString SkillName = "";

	UPROPERTY(VisibleAnywhere, Category = "info")
	FString SkillSock = "";

	UPROPERTY(VisibleAnywhere, Category = "info")
	UTexture2D* SkillImage = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "info")
	int TriPodInfo[3] = { -1, };

protected :
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta = (BindWidget))
	class USlotBaseClass *BackGroundWidget;

	UPROPERTY(meta = (BindWidget))
	class UImage* UIImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillUISock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillUIName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillUIPoint;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillUIPointText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillUIlLevel;

	UPROPERTY(meta = (BindWidget))
	class UButton* DownLevel;

	UPROPERTY(meta = (BindWidget))
	class UButton* UpLevel;

	UPROPERTY(meta = (BindWidget))
	class UImage* TripodImage;

	UPROPERTY(EditAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DataComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* TriPodDataComponent = nullptr;

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	TArray<UTexture2D*> TriPodImageAry;

	UFUNCTION()
	void SettingData();
	
	UFUNCTION()
	void SetWidgetData(UUserWidget* SettingData);

	UFUNCTION()
	void ViewSkillInfo();

	UFUNCTION()
	void HiddenSkillInfo();

	UFUNCTION()
	void SelectWidget();

	UFUNCTION()
	void ResetData();

	UFUNCTION()
	void SkillLevelUPFUC();

	UFUNCTION()
	void SkillLevelDOWNFUC();

	UFUNCTION()
	void UpdateTriPod();

	UFUNCTION()
	inline void SetSkillImage(UTexture2D* Image) { SkillImage = Image; }

	UFUNCTION()
	inline void SetSkillName(FString Name) { SkillName = Name; }

	UFUNCTION()
	inline void SetSkillSock(FString Sock) { SkillSock = Sock; }

	UFUNCTION()
	inline void SetSkillData(UDataTable* Table) { DataComponent = Table; }
	
	

	UFUNCTION()
	inline void SetTriPodData(UDataTable* Table) { TriPodDataComponent = Table; }

	UFUNCTION()
	FORCENOINLINE void SetSKillCaption(FString Caption) { SkillCaption = Caption; }

	UFUNCTION()
	FORCEINLINE void SetTriPodDataNum(int index, int Data) { TriPodInfo[index] = Data; }

	UFUNCTION()
	inline UTexture2D* GetSkillImage() { return SkillImage; }

	UFUNCTION()
	inline FString GetSkillName() { return SkillName; }

	UFUNCTION()
	inline FString GetSkillSock() { return SkillSock; }

	UFUNCTION()
	FORCEINLINE FString GetSkillCaption() { return SkillCaption; }

	UFUNCTION()
	inline UDataTable* GetSkillData() { return DataComponent; }

	UFUNCTION()
	inline int GetSkillLevel() { return SkillLevel; }

	UFUNCTION()
	FORCEINLINE UEntrySkillWidgetClass* GetThisWidget() { return this; }

	UFUNCTION()
	int GetTriPodDataNum(int index) {
		if (TriPodInfo[index] >= 0)
			return TriPodInfo[index];

		return -1; 
	}

	UFUNCTION()
	inline UDataTable* GetTriPodData() { return TriPodDataComponent; }
};
