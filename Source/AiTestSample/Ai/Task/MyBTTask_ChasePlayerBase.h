// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "MyBTTask_ChasePlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UMyBTTask_ChasePlayerBase : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

	UMyBTTask_ChasePlayerBase();
public :
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
