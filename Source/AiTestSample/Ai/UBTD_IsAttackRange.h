// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UBTD_IsAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class AITESTSAMPLE_API UUBTD_IsAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
	UUBTD_IsAttackRange();

protected :
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
public :
	UPROPERTY(EditAnywhere)
	float AttackRange = 200.f;
};
