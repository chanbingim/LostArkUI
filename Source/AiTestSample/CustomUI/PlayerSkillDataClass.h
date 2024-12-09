// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerSkillDataClass.generated.h"

USTRUCT()
struct FSkillData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SkillImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillSock = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillCaption = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* SkillDataInfo = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* TriPodData = nullptr;
};