// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Attack.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UBTTaskNode_Attack : public UBTTaskNode
{
	GENERATED_BODY()
protected :
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
public :
	UBTTaskNode_Attack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIs_Attack = false;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
