// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TestUISaveData.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UTestUISaveData : public USaveGame
{
	GENERATED_BODY()

public :
	UPROPERTY()
	UObject* SaveWidget;
};
