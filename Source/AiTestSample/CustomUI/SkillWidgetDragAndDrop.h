// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SkillWidgetDragAndDrop.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API USkillWidgetDragAndDrop : public UDragDropOperation
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variable")
	UUserWidget* selectWidget;
};
