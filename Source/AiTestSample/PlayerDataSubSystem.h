// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CustomStructClass.h"
#include "OpenAPIHandler.h"
#include "PlayerDataSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UPlayerDataSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	OpenAPIHandler APIHandler;

	//람다함수가 몇번 실행됐는지 확인할 함수
	int32 TrackLambdaExecutions = 0;

public : 
	UFUNCTION()
	void Init();

	UPROPERTY(VisibleAnywhere)
	TArray<FCharacterInfo> characterinfoList;

	UPROPERTY(VisibleAnywhere)
	FArmoryProfile playerProFile;

	UPROPERTY(VisibleAnywhere)
	TArray<FArmoryEquipment> playerArmoryEquipment;

	UPROPERTY(VisibleAnywhere)
	TArray<FArmoryAvatar> playerAvatar;

	UPROPERTY(VisibleAnywhere)
	TArray<FArmorySkills> playerSkills;

	UPROPERTY(VisibleAnywhere)
	TArray<UTexture2D *> skillImage;

	void ResponseReceivedData(FHttpResponsePtr responPtr, EStructType currentType);

	//Characterinfo 데이터 파싱 함수
	void ParseCharacterInfoData(const FString& JsonString);

	//CharaterArmories 데이터 파싱 함수
	void ParseCharaterArmories(const FString& JsonString);

};
