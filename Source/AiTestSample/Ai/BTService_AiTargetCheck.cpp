// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_AiTargetCheck.h"
#include "AiBase/AiCharacter.h"
#include "AiBase/MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_AiTargetCheck::UBTService_AiTargetCheck()
{
	NodeName = "CheckTarget";
	Interval = 1.0f;
}

void UBTService_AiTargetCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float   DetectRadios = 200.0f;

	if (nullptr == World) return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

	bool bResult = World->OverlapMultiByChannel
	(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel12,
		FCollisionShape::MakeSphere(DetectRadios),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			AAiCharacter* PlayerCharacter = Cast<AAiCharacter>(OverlapResult.GetActor());
			if (PlayerCharacter && PlayerCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMyAIController::TargetActorKey, PlayerCharacter);

				DrawDebugSphere(World, Center, DetectRadios, 16, FColor::Green, false, 0.4f);
				DrawDebugPoint(World, PlayerCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.4f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), PlayerCharacter->GetActorLocation(),
					FColor::Blue, false, 0.4f);
				return;
			}
		}
	}

	DrawDebugSphere(World, Center, DetectRadios, 16, FColor::Red, false, 0.4f);
}