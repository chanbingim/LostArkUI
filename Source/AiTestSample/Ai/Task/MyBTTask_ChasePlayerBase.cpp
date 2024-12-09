// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ChasePlayerBase.h"
#include "../../Player/AiTestSampleCharacter.h"
#include "../../Ai/AiBase/MyAIController.h" 
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UMyBTTask_ChasePlayerBase::UMyBTTask_ChasePlayerBase()
{
	NodeName = TEXT("ChasePlayerBase");
}

EBTNodeResult::Type UMyBTTask_ChasePlayerBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if(nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMyAIController::HomePosKey);
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 100.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMyAIController::TargetLocationKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
