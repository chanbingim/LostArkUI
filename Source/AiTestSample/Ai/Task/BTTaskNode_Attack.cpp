// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"
#include "../AiBase/AiCharacter.h"
#include "../AiBase/MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	bNotifyTick = true;
	bIs_Attack = false;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIs_Attack)
	{
		//�ִϸ��̼� ������ ȣ��
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
} 

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto PlayerCharacter = Cast<AAiCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == PlayerCharacter)
		return EBTNodeResult::Failed;

	PlayerCharacter->AI_Attack();
	bIs_Attack = true;

	//���ٽ��� �̿��� �Լ� ���
	PlayerCharacter->FOnAttackEnd.AddLambda([this]()->void
	{
		bIs_Attack = false;
	});

	return EBTNodeResult::InProgress;
}
