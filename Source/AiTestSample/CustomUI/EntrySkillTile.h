// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "EntrySkillTile.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UEntrySkillTile : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized();
	virtual void NativeConstruct();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CoolTimeText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KeynameText;

	UPROPERTY(meta = (BindWidget))
	class USlotBaseClass* WidgetSkillImage;

public :
	UFUNCTION()
	void SetUIText(FString KeyName);

	UFUNCTION()
	void CallCoolTime(FString cooltime);
};
