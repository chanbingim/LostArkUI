// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "../AiBase/MyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../AiBase/AiCharacter.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("PatrolAI");
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;
	
	//ControllingPawn->SetWalkSpeed(500.f);
	FVector const CurrentPos = ControllingPawn->GetActorLocation();
	FNavLocation NextPatrol;
	if(NavSystem->GetRandomReachablePointInRadius(CurrentPos, PatrolRadius, NextPatrol, nullptr))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMyAIController::TargetLocationKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
