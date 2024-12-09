// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FoldWidgetClass.generated.h"

class USizeBox;
class UButton;
class UHorizontalBox;
class UImage;
/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UFoldWidgetClass : public UUserWidget
{
	GENERATED_BODY()
private :
	UPROPERTY(VisibleAnywhere, Category = "WIDTH")
	float Current_WidgetWidth;

	UPROPERTY(EditAnywhere, Category = "WIDTH")
	float Max_WidgetWidth;

	UPROPERTY(EditAnywhere, Category = "WIDTH")
	float Min_WidgetWidth;

	UPROPERTY(VisibleAnywhere, Category = "STATE")
	bool bFoldState = false;

	UFUNCTION()
	bool ExceptWidget(UWidget* widget);
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	USizeBox* WidgetSize = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* FoldButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox = nullptr;
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMAGE")
	TArray<UTexture2D*> FoldTexture;

	UFUNCTION()
	void FoldWidget();
};
