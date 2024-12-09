// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillDataRow.generated.h"

UENUM()
enum class FSkillCategory : uint8
{
	Buf = 1 UMETA(DisplayName = "BufSkill"),
	AttackSkill = 2 UMETA(DisplayName = "AttackSkill"),
};

USTRUCT()
struct FSkillInfoData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Ne_Point;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CastingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int	neutralize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int	Partdestruction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString	SkillInfoText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SuperArmer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int	SKillCost;

};
