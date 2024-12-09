// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacter_Anim.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UPlayerCharacter_Anim : public UAnimInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	class UDataTable* DataTableComponent = nullptr;

	FTimerHandle EvansionHandle;
public :
	UPlayerCharacter_Anim();

	//VARIABLE
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;

	//FUNCTION
	UFUNCTION()
	void Play_AnimMontage(FString MontageName);

	UFUNCTION()
	inline FName GetAttackMontageName(int32 SectionIndex) { return FName(*FString::Printf(TEXT("Combo%d"), SectionIndex)); }

	UFUNCTION()
	void JumpToSectionMontage(int32 SectionIndex,FString MontageName);

	UFUNCTION(BlueprintCallable)
	void AnimNotify_AttackHitCheck();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_NextCombo();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_MoveDistance();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_EndEvansion();
};
