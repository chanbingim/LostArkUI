// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AiTargetCheck.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UBTService_AiTargetCheck : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public :
	UBTService_AiTargetCheck();
};
