// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ActorDataTableBase.generated.h"

UENUM(BlueprintType)
enum class FItemDataType : uint8
{
	EquipmentType UMETA(DisplayName = "Equipment"),
	ConsumptionType UMETA(DisplayName = "Consumption"),
};

USTRUCT()
struct FItemDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "ItemData")
	int ItemID;

	UPROPERTY(EditAnywhere, Category = "Type")
	FItemDataType ItemType;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* ItemStaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Texture")
	UTexture2D* ItemTexture2D = nullptr;
};

UCLASS()
class AITESTSAMPLE_API UActorDataTableBase : public UDataTable
{
	GENERATED_BODY()
	
};
