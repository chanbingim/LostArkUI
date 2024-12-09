// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotBaseClass.generated.h"

UENUM(BlueprintType)
enum class FSlotType : uint8
{
	UIType UMETA(DisplayName = "UIType"),
	SkillType UMETA(DisplayName = "SkillType"),
	QuickType UMETA(DisplayName = "QuickType"),
	ItemSlotType UMETA(DisplayName = "ItemSlotType"),

};

USTRUCT(BlueprintType)
struct FSkillSlotData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float Damage;

	UPROPERTY()
	float CoolTime;

	UPROPERTY()
	float CastingTime;

	UPROPERTY()
	int Neutralize;

	UPROPERTY()
	int partdestruction;

	UPROPERTY()
	int SuperArmer;

	UPROPERTY()
	float Cost;
};


/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API USlotBaseClass : public UUserWidget
{
	GENERATED_BODY()
private:
	UUserWidget* ParentWidget = nullptr;
	FVector2D DragOffset;

	UPROPERTY(EditAnywhere, Category = "SKILLINFO")
	int Level;

	FSkillSlotData slotData;
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UImage* SkillImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* WidgetSize = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlotType Type;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* SkillImgaeTexture = nullptr;

	UPROPERTY(EditAnywhere, Category = "WidgetClass", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> DragWidgetClass = nullptr;

	UFUNCTION()
	void SetWidgetImage(UTexture2D* texture);

	UFUNCTION()
	void SetWidgetSize(FVector2D size);

	UFUNCTION()
	inline void SetParentWidget(UUserWidget* parent) { ParentWidget = parent; }

	UFUNCTION()
	inline UUserWidget* GetParentWidget() { return ParentWidget; }

};
