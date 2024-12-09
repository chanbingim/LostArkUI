// Fill out your copyright notice in the Description page of Project Settings.


#include "AiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyAIController.h"
#include "../../Player/AiTestSampleCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Ai_AnimInstanceBase.h"
#include "MyAIController.h"

// Sets default values
AAiCharacter::AAiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AMyAIController::StaticClass();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AAiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MyAnimInstance = Cast<UAi_AnimInstanceBase>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AAiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAiCharacter::SetWalkSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AAiCharacter::AI_Attack()
{
	if (nullptr == MyAnimInstance)
		return;

	AMyAIController* OwnningController = Cast<AMyAIController>(GetController());
	OwnningController->GetBlackboardComponent()->SetValueAsBool(OwnningController->bCanAttackKey, false);
	MyAnimInstance->Play_AnimMontage("AttackMontage");
}

void AAiCharacter::Attack_Check()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), true, this);

	float AttackRange = 200.0f;
	float AttackRadius = 50.0f;
	float AttackDamage = 100.f;

	FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector End = Start + GetActorForwardVector() * AttackRange;

	bool hitDetected = GetWorld()->SweepSingleByChannel(
		OutHitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = hitDetected ? FColor::Green : FColor::Red;
	float DebugLifeTime = 3.0f;

	DrawDebugCapsule
	(
		GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime
	);

#endif

	if (hitDetected)
	{
		AAiTestSampleCharacter* MyPlayer = Cast<AAiTestSampleCharacter>(OutHitResult.GetActor());
		MyPlayer->GetDamage(AttackDamage);
	}
}