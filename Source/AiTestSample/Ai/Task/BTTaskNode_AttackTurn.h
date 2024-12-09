// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_AttackTurn.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UBTTaskNode_AttackTurn : public UBTTaskNode
{
	GENERATED_BODY()
public :
	UBTTaskNode_AttackTurn();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
