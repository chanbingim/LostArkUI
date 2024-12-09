// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTD_IsAttackRange.h"
#include "AiBase/AiCharacter.h"
#include "AiBase/MyAIController.h"
#include "../Player/AiTestSampleCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UUBTD_IsAttackRange::UUBTD_IsAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UUBTD_IsAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	auto CurrentController = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == CurrentController)
		return false;

	auto Target = Cast<AAiTestSampleCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMyAIController::TargetActorKey));
	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(CurrentController) <= AttackRange);
	return bResult;
}
