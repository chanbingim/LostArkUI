// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_MainGame.generated.h"

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	Default,
	popUP,
	mainWD,
};

UENUM(BlueprintType)
enum class EWidgetName : uint8
{
	WD_HPBar,
	WD_SkillUI,
	WD_SkillWidgetInFoUI,
	WD_Inventory,
};

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API AHUD_MainGame : public AHUD
{
	GENERATED_BODY()
private :
	

protected :
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "WIDGET")
	TSubclassOf<class UUserWidget> WD_HPBarClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "WIDGET")
	TSubclassOf<class UUserWidget> WD_SkillUI = nullptr;

	UPROPERTY(EditAnywhere, Category = "WIDGET")
	TSubclassOf<class UUserWidget> WD_SkillWidgetInFoUI = nullptr;

	UPROPERTY(EditAnywhere, Category = "WIDGET")
	TSubclassOf<class UUserWidget> WD_InventroyWidget = nullptr;

public :
	AHUD_MainGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	TArray<UUserWidget*> MainWidgetAry;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	TArray<UUserWidget*> popUpWidgetAry;

	UFUNCTION()
	void HUD_AddMainWidget(EWidgetName Name, const EWidgetType& findType);

	UFUNCTION()
	UUserWidget* Find_Widget(EWidgetName  Name, const EWidgetType& findType);

	UFUNCTION(BlueprintCallable)
	void UpdatePopUpWidgetZOrder(UUserWidget* clickwidget);

	UFUNCTION()
	TSubclassOf<class UUserWidget> GetWidgetClass(const EWidgetName Name);

	UFUNCTION()
	void HUD_RemoveWidget(EWidgetName Name, const EWidgetType& findType);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class UUserWidget> GetWD_HPBarClass() { return WD_HPBarClass; }
};
