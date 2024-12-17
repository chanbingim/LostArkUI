// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomJsonUtilityUnreal.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UCustomJsonUtilityUnreal : public UObject
{
	GENERATED_BODY()

public :
	template <typename StructType>
	static bool DeserializeJsonToStruct(const TSharedPtr<FJsonObject>& JsonObject, StructType& OutStruct);
};

template<typename StructType>
bool UCustomJsonUtilityUnreal::DeserializeJsonToStruct(const TSharedPtr<FJsonObject>& JsonObject, StructType& OutStruct)
{
	if (!JsonObject.IsValid()) return false;

    for (TFieldIterator<FProperty> It(StructType::StaticStruct()); It; ++It)
    {
        FProperty* Property = *It;
        FString FieldName = Property->GetName();

        // 문자열 필드 매핑
        if (FStrProperty* StrProp = CastField<FStrProperty>(Property))
        {
            StrProp->SetPropertyValue_InContainer(&OutStruct, JsonObject->GetStringField(FieldName));
        }
        // 정수 필드 매핑
        else if (FIntProperty* IntProp = CastField<FIntProperty>(Property))
        {
            IntProp->SetPropertyValue_InContainer(&OutStruct, JsonObject->GetIntegerField(FieldName));
        }
        // bool 필드 매핑
        else if (FBoolProperty* boolProp = CastField<FBoolProperty>(Property))
        {
            boolProp->SetPropertyValue_InContainer(&OutStruct, JsonObject->GetBoolField(FieldName));
        }
        // float 필드 매핑
        else if (FFloatProperty* floatProp = CastField<FFloatProperty>(Property))
        {
            floatProp->SetPropertyValue_InContainer(&OutStruct, JsonObject->GetNumberField(FieldName));
        }

        //언리얼 리플렉션(프로퍼티) 이용해서 Json 파일 파싱하려했는데 구조체 부분에서
        //명시적으로 선언을안하면 못읽어 들이는 문제 발생해서 추후 업데이트 예정
    }

	return true;
}
