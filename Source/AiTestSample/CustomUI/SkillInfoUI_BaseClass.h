// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillInfoUI_BaseClass.generated.h"

class UTextBlock;
class UImage;

USTRUCT(BlueprintType)
struct FBaseInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillNameText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* SkillImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillSockText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillCaptionText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillCoolTimeText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillLevelText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillMaNaTimeText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillInfoText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillPartdestructionText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillneutralizeText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillSuperArmerText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* SkillTriPodFristImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillTriPodFristName = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillTriPodFristLevelText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillTriPodFristInfoText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* SkillTriPodSecondImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillTriPodSecondNameText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillTriPodSecondLevelText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillTriPodSecondInfoText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* SkillTriPodThreeImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillTriPodThreeNameText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillTriPodThreeLevelText = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* SkillTriPodThreeInfoText = nullptr;
};

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API USkillInfoUI_BaseClass : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "INFO")
	FString Name;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	UTexture2D* Image = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	FString Sock;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	FString Caption;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	float CoolTime;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	float Level;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	float Dmage;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	FString Info;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	int	Partdestruction;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	int SuperArmer;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	int	neutralize;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	float SKillCost;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	TArray<UTexture2D*> TriPodImage;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	TArray<FString> TriPodName;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	TArray<float> TriPodLevel;

	UPROPERTY(VisibleAnywhere, Category = "INFO")
	TArray<FString> TriPodInfo;

protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

public :
	UFUNCTION()
	void SettingData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBaseInfo BaseOption;
};
