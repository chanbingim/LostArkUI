// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomStructClass.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY()

public:
	FCharacterInfo() {};

	UPROPERTY(VisibleAnywhere)
	FString ServerName;

	UPROPERTY(VisibleAnywhere)
	FString CharacterName;

	UPROPERTY(VisibleAnywhere)
	int32 CharacterLevel;

	UPROPERTY(VisibleAnywhere)
	FString CharacterClassName;

	UPROPERTY(VisibleAnywhere)
	FString ItemAvgLevel;

	UPROPERTY(VisibleAnywhere)
	FString ItemMaxLevel;
};

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

public :
	FCharacterStats() {};

	UPROPERTY(VisibleAnywhere)
	FString Type;

	UPROPERTY(VisibleAnywhere)
	FString Value;

	UPROPERTY(VisibleAnywhere)
	TArray<FString> ToolTip;
};

USTRUCT(BlueprintType)
struct FTendencies
{
	GENERATED_BODY()

public:
	FTendencies() {};

	UPROPERTY(VisibleAnywhere)
	FString Type;

	UPROPERTY(VisibleAnywhere)
	FString Point;

	UPROPERTY(VisibleAnywhere)
	FString MaxPoint;

};

USTRUCT(BlueprintType)
struct FArmoryEquipment
{
	GENERATED_BODY()

public:
	FArmoryEquipment() {};

	UPROPERTY(VisibleAnywhere)
	FString Type;

	UPROPERTY(VisibleAnywhere)
	FString Name;

	UPROPERTY(VisibleAnywhere)
	FString Icon;

	UPROPERTY(VisibleAnywhere)
	FString Grade;

	UPROPERTY(VisibleAnywhere)
	FString ToolTip;
};


USTRUCT(BlueprintType)
struct FArmoryAvatar
{
	GENERATED_BODY()

public:
	FArmoryAvatar() {};

	UPROPERTY(VisibleAnywhere)
	FString Type;

	UPROPERTY(VisibleAnywhere)
	FString Name;

	UPROPERTY(VisibleAnywhere)
	FString Icon;

	UPROPERTY(VisibleAnywhere)
	FString Grade;

	UPROPERTY(VisibleAnywhere)
	bool bIsSet;

	UPROPERTY(VisibleAnywhere)
	bool bIsInner;

	UPROPERTY(VisibleAnywhere)
	FString ToolTip;
};

USTRUCT(BlueprintType)
struct FArmoryProfile
{
	GENERATED_BODY()

public:
	FArmoryProfile() {};

	UPROPERTY(VisibleAnywhere)
	FString CharacterImage;

	UPROPERTY(VisibleAnywhere)
	int32 ExpeditionLevel;

	UPROPERTY(VisibleAnywhere)
	FString PvpGradeName;

	UPROPERTY(VisibleAnywhere)
	int32 TownLevel;

	UPROPERTY(VisibleAnywhere)
	FString TownName;

	UPROPERTY(VisibleAnywhere)
	FString Title;

	UPROPERTY(VisibleAnywhere)
	FString GuildMemberGrade;

	UPROPERTY(VisibleAnywhere)
	FString GuildName;

	UPROPERTY(VisibleAnywhere)
	int32 UsingSkillPoint;

	UPROPERTY(VisibleAnywhere)
	int32 TotalSkillPoint;

	UPROPERTY(VisibleAnywhere)
	TArray<FCharacterStats> stats;

	UPROPERTY(VisibleAnywhere)
	TArray<FTendencies> tendencies;

	UPROPERTY(VisibleAnywhere)
	FString ServerName;

	UPROPERTY(VisibleAnywhere)
	FString CharacterName;

	UPROPERTY(VisibleAnywhere)
	int32 CharacterLevel;

	UPROPERTY(VisibleAnywhere)
	FString CharacterClassName;

	UPROPERTY(VisibleAnywhere)
	FString ItemAvgLevel;

	UPROPERTY(VisibleAnywhere)
	FString ItemMaxLevel;

	/*ArmoryProfile operator= (const FArmoryProfile& _armoryprofile)
	{
		return _armoryprofile;
	}*/
};