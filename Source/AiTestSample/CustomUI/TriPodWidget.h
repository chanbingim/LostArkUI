// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TriPodWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

USTRUCT(BlueprintType)
struct FTriPodOption
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* ImageButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* TripodImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TripodName = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* LevelButton = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UImage* SelectImage = nullptr;
};

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UTriPodWidget : public UUserWidget
{
	GENERATED_BODY()
private :

	UPROPERTY()
	FString TriPodName;

	UPROPERTY()
	int TriPodLevel;

	UPROPERTY()
	UTexture2D* TriImage = nullptr;

	UPROPERTY()
	int TriPodNum;

protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

public :
	UFUNCTION()
	void TriPodSelect();

	UFUNCTION()
	void DataSetting();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTriPodOption ControllOption;

	FORCEINLINE void SetTriPodName(FString name) { TriPodName = name; }
	FORCEINLINE void SetTriPodNum(int num) { TriPodNum = num; }
	FORCEINLINE void SetTriPodLevel(int Level) { TriPodLevel = Level; }
	FORCEINLINE void SetTriPodImage(UTexture2D* Image) { TriImage = Image; }

	FORCEINLINE int GetTriPodNum() { return TriPodNum; }
};
