// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IHttpRequest.h"
#include "Templates/SharedPointer.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FReceiveResponseDataDele, FHttpResponsePtr);
/**
 * 
 */
struct AITESTSAMPLE_API OpenAPIHandler : public TSharedFromThis<OpenAPIHandler>
{

private : 
	FHttpModule* httpModule = nullptr;

	void HttpCall(const FString& InURL, const FString& InVerb);
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	FString urlEncode(const FString& str);

public :
	FString defaultDomainURL;
	FString apiKey;

public:
	OpenAPIHandler();

	

	// http 요청에 사용할 함수
	UFUNCTION(BlueprintCallable)
	void RequestCharacterInfo(FString charactername);

	FReceiveResponseDataDele ReceivedDataFuncDele;
};
