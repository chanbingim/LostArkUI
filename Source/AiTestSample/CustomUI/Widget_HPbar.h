// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HPbar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_Setting,float, Data1 ,float, Data2);

class UProgressBar;
class UTextBlock;
class UTileView;

USTRUCT(BlueprintType)
struct FPlayerStateUI
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProgressBar* HPBar = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* HPTextBlock = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProgressBar* MPBar = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* MPTextBlock = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* SkillQuickSlot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* ItemQuickSlot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* BattleItemQuickSlot = nullptr;
};

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UWidget_HPbar : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bar")
	FPlayerStateUI PlayerStateUI;

	FDele_Setting Dele_HPSetting;
	FDele_Setting Dele_MPSetting;

	UFUNCTION()
	void SetHpState(float CurrentHP, float MaxHP);

	UFUNCTION()
	void SetMpState(float CurrentMP, float MaxMP);

};
