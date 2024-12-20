// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IHttpRequest.h"
#include "Templates/SharedPointer.h"

UENUM(BlueprintType)
enum class EStructType : uint8
{
	None,
	charaterInfo,
	charaterArmories,
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FReceiveResponseDataDele, FHttpResponsePtr, EStructType);
DECLARE_MULTICAST_DELEGATE_TwoParams(FReceiveResponseDownloadDataDele, FHttpResponsePtr, int32);

struct AITESTSAMPLE_API OpenAPIHandler : public TSharedFromThis<OpenAPIHandler>
{

private : 
	FHttpModule* httpModule = nullptr;

	EStructType currentRequestType;

	void HttpCall(const FString& InURL, const FString& InVerb, EStructType requestDataType);
	void DownloadImage(const FString& InURL, int32 arryIndex);

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnImageDownLoadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	FString urlEncode(const FString& str);
public :
	FString SerachCharacterDomainURL = "https://developer-lostark.game.onstove.com/characters/";
	FString SerachArmoriesDomainURL = "https://developer-lostark.game.onstove.com/armories/characters/";
	FString apiKey = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsIng1dCI6IktYMk40TkRDSTJ5NTA5NWpjTWk5TllqY2lyZyIsImtpZCI6IktYMk40TkRDSTJ5NTA5NWpjTWk5TllqY2lyZyJ9.eyJpc3MiOiJodHRwczovL2x1ZHkuZ2FtZS5vbnN0b3ZlLmNvbSIsImF1ZCI6Imh0dHBzOi8vbHVkeS5nYW1lLm9uc3RvdmUuY29tL3Jlc291cmNlcyIsImNsaWVudF9pZCI6IjEwMDAwMDAwMDA1Njk4NjMifQ.dV2eIc-Jtuz9NGmZ0B2aC0tQNUcmqidQABY8iSuls8jGn1iBeU2tHXFj1ijBnaGT8XKndU-WL1P0kzJrDyxrXYwEAIZnbJTQQI9OwcZyVHO0VHcJpDfHdE6ghWv_gjFZyAAKBpPEahCHoTfwFC5NpKFI3KzizuKK8tPlk6xdi07yZtS9gbkHRI-4HaqipeaISuVeqMpeytUsP0yBT0hL0IdL8pp5CWwbePjMFHh0HEjsz9Y17DFnd52ZC1Z7H2MVLbRpQ3oOXgAgUckyFYddgrR7nD4SkZaqAbl1z13BxVIvFiV4IGwuB0Ah9-iF44yIX1ZdFRLQKucAXjFzvNyWDw";

public:
	OpenAPIHandler();

	// http 요청에 사용할 함수
	UFUNCTION(BlueprintCallable)
	void RequestCharacterInfo(FString charactername);

	UFUNCTION(BlueprintCallable)
	void RequestWebServerFormImageData(FString imageURL, int32 arryIndex);

	UFUNCTION(BlueprintCallable,
		meta (ToolTip = "charcetername is your LostArk CharacterName, filters =  profiles+equipment+avatars+combat-skills+engravings+cards+gems+colosseums+collectibles+arkpassive"))
	void RequestCharacterArmories(FString charactername, FString filters);

	FReceiveResponseDataDele ReceivedDataFuncDele;
	FReceiveResponseDownloadDataDele ReceiveDwonloadImageDele;
};
