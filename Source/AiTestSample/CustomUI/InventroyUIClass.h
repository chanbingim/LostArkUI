// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpwidgetBase.h"
#include "InventroyUIClass.generated.h"


class UButton;
class UTileView;

USTRUCT(BlueprintType)
struct FInvenToryWidgetOption
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* MoveWidgetButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* ExitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTileView* tileView;
};
/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UInventroyUIClass : public UPopUpwidgetBase
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTexture2D*> ItemTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInvenToryWidgetOption InvenOption;
	
public : 
	UFUNCTION()
	void HandleTileViewItemClicked(UObject* ClickedItem);

	UFUNCTION()
	void CloseWidget();

	UFUNCTION(BlueprintCallable)
	void ItemSetting();

	UFUNCTION()
	void UIRefesh(UObject* FromWidget, UObject* ToWidget);
};
