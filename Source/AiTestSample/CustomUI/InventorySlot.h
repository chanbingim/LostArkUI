// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotBaseClass.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UInventorySlot : public USlotBaseClass, public IUserObjectListEntry
{
	GENERATED_BODY()
protected : 
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ItemCount = nullptr;

public :
	UPROPERTY(EditAnywhere, Category = "ItemData")
	int Count;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	int item_ID;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	int SlotIndex;

	UFUNCTION()
	void SetItemData();

};
