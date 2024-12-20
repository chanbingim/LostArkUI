// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenAPIHandler.h"

OpenAPIHandler::OpenAPIHandler()
{
	httpModule = &FHttpModule::Get();
}

FString OpenAPIHandler::urlEncode(const FString& str)
{
	FString unreserved = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~";
	FString escaped = "";
	int32 index = 1;
	for (size_t i = 0; i < str.Len(); i++)
	{
		if (str[i] >= 0x20 && str[i] <= 0x7E)
		{
			escaped.AppendChar(str[i]);  // 아스키 코드 범위에 있는 문자들은 그대로 추가
		}
		else
		{
			escaped.Append("%");
			char buf[3];
			 
			/* char를 unsigned char로 바꿔주어야 합니다.
			 * (그렇지 않으면 한글 등의 문자를 제대로 변환하지 못합니다.)
			 */
			sprintf(buf, "%.2X", (unsigned char)str[i]);
			escaped.Append(buf);
		}
	}
	return escaped;
}


void OpenAPIHandler::RequestWebServerFormImageData(FString imageURL, int32 arryIndex)
{
	DownloadImage(imageURL, arryIndex);
}

void OpenAPIHandler::RequestCharacterInfo(FString charactername)
{
	FString resultURL = SerachCharacterDomainURL + urlEncode(charactername) + "/siblings";
	HttpCall(resultURL, "Get", EStructType::charaterInfo);
}

void OpenAPIHandler::RequestCharacterArmories(FString charactername, FString filters)
{
	FString resultURL = SerachArmoriesDomainURL + urlEncode(charactername);

	if(!filters.IsEmpty())
		resultURL = resultURL + "?" + urlEncode(filters);

	HttpCall(resultURL, "Get", EStructType::charaterArmories);
}

void OpenAPIHandler::HttpCall(const FString& InURL, const FString& InVerb, EStructType requestDataType)
{
	TSharedPtr<IHttpRequest> Request = httpModule->CreateRequest();
	Request->OnProcessRequestComplete().BindRaw(this, &OpenAPIHandler::OnResponseReceived);

	//HTTP 도메인 주소
	Request->SetURL(InURL);
#pragma region Http Method
	//HTTP 매서드 (Get, POST등)
	//GET: 리소스를 조회할 때 사용한다.데이터의 변경 없이 서버로부터 데이터를 가져온다.
	//POST : 서버에 데이터를 제출할 때 사용한다.일반적으로 리소스를 생성할 때 사용된다.
	//PUT : 서버의 리소스를 업데이트할 때 사용한다.
	//DELETE : 서버의 리소스를 삭제할 때 사용한다.
	//PATCH : 리소스의 일부를 업데이트할 때 사용한다.
	Request->SetVerb(InVerb);
#pragma endregion
	//서버가 미리 알수있도록 하는 함수
	//서버가 어떤종류의 데이터를 받을지 지정하는 함수
	//header 종류 : https://velog.io/@jkijki12/HTTP-Header-%EC%A0%95%EB%A6%AC
	FString ResultApiKey = "bearer " + apiKey;

	//json 파일로 accept 연동
	Request->SetHeader("accept", TEXT("application/Json"));

	//Lost Ark 오픈 api 키값
	Request->SetHeader("authorization", ResultApiKey);

	//응답하는 내용의 타입과 문자 포맷을 표현한다.
	Request->SetHeader("Content-Type", TEXT("application/Json"));

	// 요청 타입을 매개변수로 전달
	FString RequestTypeStr = FString::Printf(TEXT("%d"), static_cast<int32>(requestDataType));
	Request->SetHeader(TEXT("Request-Type"), RequestTypeStr);
	UE_LOG(LogTemp, Warning, TEXT("Response Code: %s"), *RequestTypeStr);

#pragma region Post Example
	//Post즉 서버에 데이터를 올릴때 사용하는 구조
	//TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	//RequestObj->SetStringField("Type", "");
	//RequestObj->SetStringField("Name", "");
	//RequestObj->SetStringField("Icon", "");
	//RequestObj->SetStringField("Grade", "");
	//RequestObj->SetStringField("Tooltip", "");

	//FString RequestBody;
	//TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	//FJsonSerializer::Serialize(RequestObj, Writer);

	//Request->SetContentAsString(RequestBody);
#pragma endregion
	//서버에 요청
	Request->ProcessRequest();
	// 전송했음을 알리는 로그 출력
	UE_LOG(LogTemp, Warning, TEXT("HttpCall initiated. URL: %s, Verb: %s"), *InURL, *InVerb);
}

void OpenAPIHandler::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// 요청이 성공했는지, 응답이 유요한지 검사한다.
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP request failed. URL: %s"), *Request->GetURL());
		return;
	}

	// Code가 200일 때만 정상작동
	// Code 확인 URL: https://developer-lostark.game.onstove.com/usage-guide#API-CHARACTERS
	int32 ResponseCode = Response->GetResponseCode();
	FString RequestTypeStr = Request->GetHeader(TEXT("Request-Type"));
	EStructType RequestType = static_cast<EStructType>(FCString::Atoi(*RequestTypeStr));

	UE_LOG(LogTemp, Warning, TEXT("Response Code: %d"), ResponseCode);
	UE_LOG(LogTemp, Warning, TEXT("Response Code: %s"), *RequestTypeStr);

	ReceivedDataFuncDele.Broadcast(Response, RequestType);
}

void OpenAPIHandler::DownloadImage(const FString& InURL, int32 arryIndex)
{
	TSharedPtr<IHttpRequest> Request = httpModule->CreateRequest();
	Request->OnProcessRequestComplete().BindRaw(this, &OpenAPIHandler::OnImageDownLoadComplete);

	//HTTP 도메인 주소
	Request->SetURL(InURL);
#pragma region Http Method
	//HTTP 매서드 (Get, POST등)
	//GET: 리소스를 조회할 때 사용한다.데이터의 변경 없이 서버로부터 데이터를 가져온다.
	//POST : 서버에 데이터를 제출할 때 사용한다.일반적으로 리소스를 생성할 때 사용된다.
	//PUT : 서버의 리소스를 업데이트할 때 사용한다.
	//DELETE : 서버의 리소스를 삭제할 때 사용한다.
	//PATCH : 리소스의 일부를 업데이트할 때 사용한다.
	Request->SetVerb("Get");
#pragma endregion

	//json 파일로 accept 연동
	Request->SetHeader("accept", TEXT("application/Json"));

	//응답하는 내용의 타입과 문자 포맷을 표현한다.
	Request->SetHeader("Content-Type", TEXT("application/Json"));

	Request->SetHeader(TEXT("Request-Type"), FString::FromInt(arryIndex));

	//서버에 요청
	Request->ProcessRequest();
	UE_LOG(LogTemp, Warning, TEXT("DownloadImage L: %s"), *InURL);

}

void OpenAPIHandler::OnImageDownLoadComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// 요청이 성공했는지, 응답이 유요한지 검사한다.
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP request failed. URL: %s"), *Request->GetURL());
		return;
	}

	FString RequestTypeStr = Request->GetHeader(TEXT("Request-Type"));
	int32 arryIndex = FCString::Atoi(*RequestTypeStr);

	ReceiveDwonloadImageDele.Broadcast(Response, arryIndex);
}
