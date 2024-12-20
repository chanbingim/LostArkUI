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

protected :
	virtual void BeginPlay();

public:
	UPROPERTY(VisibleAnywhere)
	TArray<UTexture2D*> sampletexture;

	AAiTestSampleGameMode();


};