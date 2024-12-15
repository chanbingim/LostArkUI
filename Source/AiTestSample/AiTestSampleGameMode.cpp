// Copyright Epic Games, Inc. All Rights Reserved.

#include "AiTestSampleGameMode.h"

#include "Player/AiTestSamplePlayerController.h"
#include "Player/AiTestSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAiTestSampleGameMode::AAiTestSampleGameMode()
{
	
}

void AAiTestSampleGameMode::BeginPlay()
{
	APIHandler.defaultDomainURL = "https://developer-lostark.game.onstove.com/characters/";
	APIHandler.apiKey = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsIng1dCI6IktYMk40TkRDSTJ5NTA5NWpjTWk5TllqY2lyZyIsImtpZCI6IktYMk40TkRDSTJ5NTA5NWpjTWk5TllqY2lyZyJ9.eyJpc3MiOiJodHRwczovL2x1ZHkuZ2FtZS5vbnN0b3ZlLmNvbSIsImF1ZCI6Imh0dHBzOi8vbHVkeS5nYW1lLm9uc3RvdmUuY29tL3Jlc291cmNlcyIsImNsaWVudF9pZCI6IjEwMDAwMDAwMDA1Njk4NjMifQ.dV2eIc-Jtuz9NGmZ0B2aC0tQNUcmqidQABY8iSuls8jGn1iBeU2tHXFj1ijBnaGT8XKndU-WL1P0kzJrDyxrXYwEAIZnbJTQQI9OwcZyVHO0VHcJpDfHdE6ghWv_gjFZyAAKBpPEahCHoTfwFC5NpKFI3KzizuKK8tPlk6xdi07yZtS9gbkHRI-4HaqipeaISuVeqMpeytUsP0yBT0hL0IdL8pp5CWwbePjMFHh0HEjsz9Y17DFnd52ZC1Z7H2MVLbRpQ3oOXgAgUckyFYddgrR7nD4SkZaqAbl1z13BxVIvFiV4IGwuB0Ah9-iF44yIX1ZdFRLQKucAXjFzvNyWDw";
	APIHandler.RequestCharacterInfo("감자밭농민");
	APIHandler.ReceivedDataFuncDele.AddUObject(this, &ThisClass::ResponseReceivedData);
}

void AAiTestSampleGameMode::ResponseReceivedData(FHttpResponsePtr responPtr)
{
	// 직렬화를 통해서 Write를 하고
	// 역직렬화 를 통해서 Read 함
	//Json을 역직렬화를 통해서 JsonData를 받아옴
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(responPtr->GetContentAsString());

	UE_LOG(LogTemp, Warning, TEXT("Tittle : %s"), *responPtr->GetContentAsString());
	if (FJsonSerializer::Deserialize(Reader, JsonArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : JsonArray) {
			TSharedPtr<FJsonObject> JsonObject = Value->AsObject();

			FCharacterInfo tempcharacterinfo;
			if (JsonObject.IsValid()) {
				tempcharacterinfo.ServerName = JsonObject->GetStringField("ServerName");
				tempcharacterinfo.CharacterName = JsonObject->GetStringField("CharacterName");
				tempcharacterinfo.CharacterLevel = JsonObject->GetIntegerField("CharacterLevel");
				tempcharacterinfo.CharacterClassName = JsonObject->GetStringField("CharacterClassName");
				tempcharacterinfo.ItemAvgLevel = JsonObject->GetStringField("ItemAvgLevel");
				tempcharacterinfo.ItemMaxLevel = JsonObject->GetStringField("ItemMaxLevel");
				characterinfoList.Add(tempcharacterinfo);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Deserialize Fail"));
	}
}
