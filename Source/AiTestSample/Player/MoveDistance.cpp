// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveDistance.h"


void UMoveDistance::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	/*IMontageInterface* AttackPawn = Cast<IMontageInterface>(MeshComp->GetOwner());

	if (nullptr != AttackPawn)
	{
		AttackPawn->Attack_Check();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));
	}*/
}