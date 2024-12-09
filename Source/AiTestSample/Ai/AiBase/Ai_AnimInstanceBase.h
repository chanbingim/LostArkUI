// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Ai_AnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UAi_AnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

private :
	UPROPERTY(EditAnywhere,  Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DataTableComponent = nullptr;

public :
	UFUNCTION(BlueprintCallable)
	void AnimNotify_ResetAttack();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_EndHit();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_MonsterDeath();

	UFUNCTION()
	void Play_AnimMontage(FString MontageName);
};
