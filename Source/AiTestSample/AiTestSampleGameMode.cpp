// Copyright Epic Games, Inc. All Rights Reserved.

#include "AiTestSampleGameMode.h"
#include "CustomJsonUtilityUnreal.h"
#include "JsonObjectConverter.h"
#include "PlayerDataSubSystem.h"
#include "Player/AiTestSamplePlayerController.h"
#include "Player/AiTestSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAiTestSampleGameMode::AAiTestSampleGameMode()
{
	
}

void AAiTestSampleGameMode::BeginPlay()
{
	auto playerData = GetGameInstance()->GetSubsystem<UPlayerDataSubSystem>();

	UE_LOG(LogTemp, Warning, TEXT("Load Image : %d"), playerData->skillImage.Num());
	for (int i = 0; i < playerData->skillImage.Num(); i++)
	{
		sampletexture.Add(playerData->skillImage[i]);
	}
}

