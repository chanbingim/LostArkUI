// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoodsWidget_IconClass.generated.h"

class UButton;
class USizeBox;
class UTextBlock;

UENUM(BlueprintType)
enum class TypeIcon : uint8
{
	Message,
	LoaTalk,
	CoinBox,
};

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UGoodsWidget_IconClass : public UUserWidget
{
	GENERATED_BODY()

private :
	UPROPERTY(EditAnywhere, Category = "STATE")
	TArray<UTexture2D*> IconImage;

	UPROPERTY(EditAnywhere, Category = "STATE")
	TypeIcon tIcon;

	UPROPERTY(VisibleAnywhere, Category = "STATE")
	int ArlamCount = 0;

	UFUNCTION()
	void WidgetImageSelect();
protected :
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	USizeBox* WidgetSize = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* IconButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* VariableText = nullptr;
public :
	UFUNCTION()
	void WidgetClicked();
};
