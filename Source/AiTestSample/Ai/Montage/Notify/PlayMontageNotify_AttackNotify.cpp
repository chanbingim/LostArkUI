// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMontageNotify_AttackNotify.h"
#include "../MontageInterface.h"

void UPlayMontageNotify_AttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IMontageInterface* AttackPawn = Cast<IMontageInterface>(MeshComp->GetOwner());

		if (nullptr != AttackPawn)
		{
			AttackPawn->Attack_Check();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));
		}
	}
}
