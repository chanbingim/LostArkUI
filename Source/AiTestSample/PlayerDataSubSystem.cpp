// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDataSubSystem.h"
#include "CustomJsonUtilityUnreal.h"
#include "Kismet/GameplayStatics.h"
#include "AiTestSample/CustomUI/HUD_MainGame.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "AiTestSampleGameMode.h"
#include "AiTestSample/CustomUI/SkillWidgetClass.h"
#include "ImageUtils.h"
#include "JsonObjectConverter.h"

void UPlayerDataSubSystem::Init()
{
	APIHandler.RequestCharacterInfo("감자밭농민");
	APIHandler.ReceivedDataFuncDele.AddUObject(this, &ThisClass::ResponseReceivedData);
	APIHandler.RequestCharacterArmories("감자밭농민", "filters=profiles+equipment+avatars+combat-skills");
}

void UPlayerDataSubSystem::ResponseReceivedData(FHttpResponsePtr responPtr, EStructType currentType)
{
	// 직렬화를 통해서 Write를 하고
	// 역직렬화 를 통해서 Read 함
	//Create a reader pointer to read the json data

	if (EStructType::charaterInfo == currentType)
		ParseCharacterInfoData(responPtr->GetContentAsString());
	if (currentType == EStructType::charaterArmories)
		ParseCharaterArmories(responPtr->GetContentAsString());

	
}

void UPlayerDataSubSystem::ParseCharacterInfoData(const FString& JsonString)
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

void UPlayerDataSubSystem::ParseCharaterArmories(const FString& JsonString)
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

		if (structJsonObj->HasField(TEXT("ArmorySkills")))
		{
			TArray<TSharedPtr<FJsonValue>> jsonVal = structJsonObj->GetArrayField(TEXT("ArmorySkills"));
			
			TWeakObjectPtr<UPlayerDataSubSystem> WeakThis = this;

			skillImage.Init(nullptr, jsonVal.Num());
			TrackLambdaExecutions = 0;
			//람다는 특정 시점을 기준으로 데이터를 캡처해서 보관
			//때문에 반복문안에서 람다를 사용하면 람다식이 여러번 중첩되어 실행되는결과가 나옴
			//그 때문에 밖으로 빼서 람다를 적용시키고 서버에서 데이터를 요청할때 Index를 넣어서 같이 받기로 했다.
			APIHandler.ReceiveDwonloadImageDele.AddLambda([WeakThis](FHttpResponsePtr Response, int32 Index)
				{
					if (WeakThis.IsValid())
					{
						//URL링크에 있는 HTML 코드를 바이너리 코드로 바꿔서 텍스쳐 이미지로 가져옴
						UTexture2D* DownloadedTexture = UKismetRenderingLibrary::ImportBufferAsTexture2D(WeakThis->GetWorld(), Response->GetContent());
						if (DownloadedTexture)
						{
							//요청한 인덱스 크기가 SkillImage 배열보다 크기가 크다면 리턴
							if (Index > WeakThis->skillImage.Num() - 1)
								return;

							WeakThis->skillImage[Index] = DownloadedTexture;
							UE_LOG(LogTemp, Warning, TEXT("Resouce Create Success %s"), *DownloadedTexture->GetName());
						}
						else
							UE_LOG(LogTemp, Warning, TEXT("Resouce Create Fail"));

						WeakThis->TrackLambdaExecutions++;
						if (WeakThis->skillImage.Num() <= WeakThis->TrackLambdaExecutions)
						{
							//일단 생각이 안나서 특정 위젯을 초기화 시키는 방식으로 갔는데
							//여기서 내가 생각할때는 데이터가 필요한 위젯들을 델리게이트 형태로 리셋 시키는게 좋아보임
							auto gameHud = Cast<AHUD_MainGame>(UGameplayStatics::GetPlayerController(WeakThis.Get(), 0)->GetHUD());
							auto skillWidget = Cast<USkillWidgetClass>
								(gameHud->Find_Widget(EWidgetName::WD_SkillUI, EWidgetType::popUP));
							skillWidget->NativeConstruct();
						}
					}
				}
			);

			for (int i = 0; i < jsonVal.Num(); i++)//auto dataJson : jsonVal)
			{
				FArmorySkills tempCharacterSkill;
				FJsonObjectConverter::JsonObjectToUStruct(jsonVal[i]->AsObject().ToSharedRef(), &tempCharacterSkill);

				APIHandler.RequestWebServerFormImageData(tempCharacterSkill.Icon, i);
				playerSkills.Add(tempCharacterSkill);
			}
		}
	}
}
