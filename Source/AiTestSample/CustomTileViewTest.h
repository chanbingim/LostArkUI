// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TileView.h"
#include "CustomTileViewTest.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UCustomTileViewTest : public UTileView
{
	GENERATED_BODY()

protected :
	virtual void OnItemClickedInternal(UObject* Item);

	
};
