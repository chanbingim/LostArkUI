// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayMontageNotify_AttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UPlayMontageNotify_AttackNotify : public UAnimNotify
{
	GENERATED_BODY()
	
protected: 
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
