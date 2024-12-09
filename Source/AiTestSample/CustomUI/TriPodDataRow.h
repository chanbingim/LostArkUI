// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TriPodDataRow.generated.h"

USTRUCT()
struct FTriPodData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TriPodImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TriPodName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TriPodLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TriPodInfo = "";
};