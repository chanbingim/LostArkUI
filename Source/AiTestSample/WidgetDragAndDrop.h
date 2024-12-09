// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WidgetDragAndDrop.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UWidgetDragAndDrop : public UDragDropOperation
{
	GENERATED_BODY()
public :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MoveUMG")
	class UUserWidget* SelectWidget = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DragOFFSET")
	FVector2D DragOffSet;
};
