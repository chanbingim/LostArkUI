// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoinViewWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleReserves,int, Coin);

class UImage;
class USizeBox;
class UTextBlock;

UENUM(BlueprintType)
enum class TypeCoin : uint8
{
	shilling,
	Gold,
	Crystal,
};

UCLASS()
class AITESTSAMPLE_API UCoinViewWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, Category = "STATE")
	int	Reserves;

	UPROPERTY(EditAnywhere, Category = "STATE")
	TypeCoin tCoin;

	UFUNCTION()
	void SetReserves(int Data);

	UFUNCTION()
	void SetCoinImage();
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	USizeBox* WidgetSize = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WidgetText = nullptr; 

	UPROPERTY(meta = (BindWidget))
	UImage* WidgetImage = nullptr;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IMAGE")
	TArray<UTexture2D*> CoinTexture;

	FDeleReserves FDele_RSetting;
};
