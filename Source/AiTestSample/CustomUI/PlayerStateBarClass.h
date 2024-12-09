// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateBarClass.generated.h"

class UCanvasPanel;
class UPanelSlot;
/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UPlayerStateBarClass : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainCanvas;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TArray<UUserWidget*> ActiveWidget;

	UFUNCTION()
	UUserWidget* GetHPBar();

	UFUNCTION()
	USkillWidgetClass* GetSkillWidget();

	UFUNCTION()
	void CanvasAddToWidget(UUserWidget* newWidget);

	UFUNCTION()
	UCanvasPanel* GetMainCanvas() { return MainCanvas; }

	void MoveSkillUI(FVector2D MousePos, TObjectPtr<UPanelSlot> _slot);
};
