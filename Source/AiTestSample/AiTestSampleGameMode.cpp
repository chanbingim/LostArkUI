// Copyright Epic Games, Inc. All Rights Reserved.

#include "AiTestSampleGameMode.h"
#include "CustomJsonUtilityUnreal.h"
#include "JsonObjectConverter.h"
#include "Player/AiTestSamplePlayerController.h"
#include "Player/AiTestSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAiTestSampleGameMode::AAiTestSampleGameMode()
{
	
}

void AAiTestSampleGameMode::BeginPlay()
{
	APIHandler.RequestCharacterInfo("나는돌격");
	APIHandler.ReceivedDataFuncDele.AddUObject(this, &ThisClass::ResponseReceivedData);

	APIHandler.RequestCharacterArmories("나는돌격", "filters=profiles+equipment+avatars");
}

//데이터 맵핑
void AAiTestSampleGameMode::ResponseReceivedData(FHttpResponsePtr responPtr, EStructType currentType)
{
	// 직렬화를 통해서 Write를 하고
	// 역직렬화 를 통해서 Read 함
	//Create a reader pointer to read the json data
	
	if (EStructType::charaterInfo == currentType)
		ParseCharacterInfoData(responPtr->GetContentAsString());
	if (currentType == EStructType::charaterArmories)
		ParseCharaterArmories(responPtr->GetContentAsString());
}

void AAiTestSampleGameMode::ParseCharacterInfoData(const FString& JsonString)
{
	//Json을 역직렬화를 통해서 JsonData를 받아옴
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(Reader, JsonArray))
	{
		for (const TSharedPtr<FJsonValue>& Value : JsonArray)
		{
			TSharedPtr<FJsonObject> JsonObject = Value->AsObject();
			FCharacterInfo tempcharacterinfo;

			if (UCustomJsonUtilityUnreal::DeserializeJsonToStruct<FCharacterInfo>(JsonObject, tempcharacterinfo))
			{
				characterinfoList.Add(tempcharacterinfo);
			}
		}
	}
}

void AAiTestSampleGameMode::ParseCharaterArmories(const FString& JsonString)
{
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(JsonString);
	TSharedPtr<FJsonObject> structJsonObj = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(Reader, structJsonObj))
	{
		if (structJsonObj->HasField(TEXT("ArmoryProfile")))
		{
			TSharedPtr<FJsonObject> JsonObject = structJsonObj->GetObjectField(TEXT("ArmoryProfile"));
			FArmoryProfile tempcharacterProfile;

			FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &tempcharacterProfile);
			playerProFile = tempcharacterProfile;
		}

		if (structJsonObj->HasField(TEXT("ArmoryEquipment")))
		{
			TArray<TSharedPtr<FJsonValue>> jsonVal = structJsonObj->GetArrayField(TEXT("ArmoryEquipment"));

			for (auto dataJson : jsonVal)
			{
				FArmoryEquipment tempCharacterArmoryEquipment;

				FJsonObjectConverter::JsonObjectToUStruct(dataJson->AsObject().ToSharedRef(), &tempCharacterArmoryEquipment);
				playerArmoryEquipment.Add(tempCharacterArmoryEquipment);
			}
		}

		if (structJsonObj->HasField(TEXT("ArmoryAvatars")))
		{
			TArray<TSharedPtr<FJsonValue>> jsonVal = structJsonObj->GetArrayField(TEXT("ArmoryAvatars"));

			for (auto dataJson : jsonVal)
			{
				FArmoryAvatar tempCharacterAvator;

				FJsonObjectConverter::JsonObjectToUStruct(dataJson->AsObject().ToSharedRef(), &tempCharacterAvator);
				playerAvatar.Add(tempCharacterAvator);
			}
		}
	}
}
