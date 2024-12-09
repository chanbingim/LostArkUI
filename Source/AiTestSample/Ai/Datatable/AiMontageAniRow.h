// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AiMontageAniRow.generated.h"

USTRUCT()
struct FMontageData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* MontageData = nullptr;
};
