// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OpenAPIHandler.h"
#include "AiTestSampleGameMode.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_USTRUCT_BODY()

public :
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

UCLASS(minimalapi)
class AAiTestSampleGameMode : public AGameModeBase
{
	GENERATED_BODY()

private :
	OpenAPIHandler APIHandler;
	
protected :
	virtual void BeginPlay();

public:
	AAiTestSampleGameMode();

	UPROPERTY(VisibleAnywhere)
	TArray<FCharacterInfo> characterinfoList;

	void ResponseReceivedData(FHttpResponsePtr responPtr);
};