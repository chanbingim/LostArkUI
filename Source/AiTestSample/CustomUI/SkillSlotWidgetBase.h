// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotBaseClass.h"
#include "SkillSlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API USkillSlotWidgetBase : public USlotBaseClass
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Name")
	FString SlotNameText = "";

	UPROPERTY(EditAnywhere, Category = "Name")
	FString SkillCoolText = "";
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SlotTextBlock = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SkillCoolTextBlock = nullptr;
};
