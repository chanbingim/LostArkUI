// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai_AnimInstanceBase.h"
#include "AiCharacter.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Datatable/AiMontageAniRow.h"

void UAi_AnimInstanceBase::Play_AnimMontage(FString MontageName)
{
	FMontageData* MontageData = DataTableComponent->FindRow<FMontageData>(FName(MontageName), " ");

	if (nullptr == MontageData || MontageData->MontageData == nullptr)
		return;

	Montage_Play(MontageData->MontageData, 1.0f);
}

void UAi_AnimInstanceBase::AnimNotify_ResetAttack()
{
	AAiCharacter* OwnerPawn = Cast<AAiCharacter>(GetOwningActor());
	AMyAIController* AiOwnningController = Cast<AMyAIController>(OwnerPawn->GetController());
	//플레이어 공격끝
	OwnerPawn->FOnAttackEnd.Broadcast();
	AiOwnningController->GetBlackboardComponent()->SetValueAsBool(AiOwnningController->bCanAttackKey, true);
}

void UAi_AnimInstanceBase::AnimNotify_EndHit()
{
	AAiCharacter* OwnerPawn = Cast<AAiCharacter>(GetOwningActor());
	AMyAIController* AiOwnningController = Cast<AMyAIController>(OwnerPawn->GetController());

	bool bCanAttack = AiOwnningController->GetBlackboardComponent()->GetValueAsBool(AiOwnningController->bCanAttackKey);

	if (!bCanAttack)
	{
		OwnerPawn->FOnAttackEnd.Broadcast();
		AiOwnningController->GetBlackboardComponent()->SetValueAsBool(AiOwnningController->bCanAttackKey, true);
	}
		
}

void UAi_AnimInstanceBase::AnimNotify_MonsterDeath()
{
	AAiCharacter* OwnerPawn = Cast<AAiCharacter>(GetOwningActor());
	AMyAIController* AiOwnningController = Cast<AMyAIController>(OwnerPawn->GetController());

	OwnerPawn->Destroy();
}
