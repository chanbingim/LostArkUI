// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter_Anim.h"
#include "AiTestSampleCharacter.h"
#include "AiTestSamplePlayerController.h"
#include "../Ai/Datatable/AiMontageAniRow.h"

UPlayerCharacter_Anim::UPlayerCharacter_Anim()
{

}

void UPlayerCharacter_Anim::Play_AnimMontage(FString MontageName)
{
	FMontageData* MontageData = DataTableComponent->FindRow<FMontageData>(FName(MontageName), " ");

	if (nullptr == MontageData || MontageData->MontageData == nullptr)
		return;

	Montage_Play(MontageData->MontageData, 1.0f);
}

void UPlayerCharacter_Anim::JumpToSectionMontage(int32 SectionIndex, FString MontageName)
{
	FName SectionName = GetAttackMontageName(SectionIndex);
	FMontageData* MontageData = DataTableComponent->FindRow<FMontageData>(FName(MontageName), " ");

	Montage_JumpToSection(SectionName, MontageData->MontageData);
}

void UPlayerCharacter_Anim::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UPlayerCharacter_Anim::AnimNotify_NextCombo()
{
	OnNextAttackCheck.Broadcast();
}

void UPlayerCharacter_Anim::AnimNotify_MoveDistance()
{
	AAiTestSampleCharacter* OwnningPawn = Cast<AAiTestSampleCharacter>(TryGetPawnOwner());
	AAiTestSamplePlayerController* OwnningController = Cast<AAiTestSamplePlayerController>(OwnningPawn->GetController());

	if (OwnningController->bMoveEvansion)
		return;

	FVector pawnLoc = OwnningPawn->GetActorLocation();
	FVector pawnForward = OwnningPawn->GetActorForwardVector() * OwnningController->DistanceRange;
	FVector newLoc = pawnLoc + pawnForward;

	OwnningPawn->LaunchCharacter(pawnForward,false, false);
	OwnningController->bMoveEvansion = true;
	GetWorld()->GetTimerManager().SetTimer(EvansionHandle, FTimerDelegate::CreateLambda(
		[this]()
		{
			AAiTestSampleCharacter* OwnningPawn = Cast<AAiTestSampleCharacter>(TryGetPawnOwner());
			AAiTestSamplePlayerController* OwnningController = Cast<AAiTestSamplePlayerController>(OwnningPawn->GetController());
			OwnningController->bMoveEvansion = false;
		}
	), OwnningController->EvansionCoolTime, false);
}

void UPlayerCharacter_Anim::AnimNotify_EndEvansion()
{
//	GetWorld()->GetTimerManager().ClearTimer(EvansionHandle);
}
