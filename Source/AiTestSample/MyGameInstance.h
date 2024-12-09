// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	class UDataTable* ItemDataTable = nullptr;
};
