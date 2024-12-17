// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OpenAPIHandler.h"
#include "CustomStructClass.h"
#include "AiTestSampleGameMode.generated.h"



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

	UPROPERTY(VisibleAnywhere)
	FArmoryProfile playerProFile;

	UPROPERTY(VisibleAnywhere)
	TArray<FArmoryEquipment> playerArmoryEquipment;

	UPROPERTY(VisibleAnywhere)
	TArray<FArmoryAvatar> playerAvatar;

	void ResponseReceivedData(FHttpResponsePtr responPtr, EStructType currentType);

	//Characterinfo 데이터 파싱 함수
	void ParseCharacterInfoData(const FString& JsonString);

	//CharaterArmories 데이터 파싱 함수
	void ParseCharaterArmories(const FString& JsonString);
};