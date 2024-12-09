// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_AttackTurn.h"
#include "../AiBase/AiCharacter.h"
#include "../AiBase/MyAIController.h"
#include "../../Player/AiTestSampleCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_AttackTurn::UBTTaskNode_AttackTurn()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTaskNode_AttackTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto EnemyCharacter = Cast<AAiCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == EnemyCharacter)
		return EBTNodeResult::Failed;

	auto Target = Cast<AAiTestSampleCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMyAIController::TargetActorKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - EnemyCharacter->GetActorLocation();
	LookVector.Z = 0;

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	EnemyCharacter->SetActorRotation(FMath::RInterpTo(EnemyCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	
	return EBTNodeResult::Succeeded;
}
