// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotBaseClass.h"
#include "ItemSlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UItemSlotWidgetBase : public USlotBaseClass
{
	GENERATED_BODY()

private :
	UPROPERTY(EditAnywhere, Category = "Name")
	FString SlotNameText = "";

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* SlotTextBlock = nullptr;

public :

};
