// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UBTTask_Patrol : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

	UBTTask_Patrol();
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PatrolRadius;
};
