// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GamePlayStatics.h"
#include "AiCharacter.h"
#include "BehaviorTree/BlackboardData.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/CapsuleComponent.h"
#include "../../Player/AiTestSampleCharacter.h"
#include "Ai_AnimInstanceBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "../AIBlackBoard_TypeHuman.h"

//unreal Key Conneted BlackBoard
const FName AMyAIController::TargetActorKey(TEXT("TargetActor"));
const FName AMyAIController::HomePosKey(TEXT("HomePos"));
const FName AMyAIController::TargetLocationKey(TEXT("TargetLocation"));
const FName AMyAIController::bCanSeePlayerKey(TEXT("bCanSeePlayer"));
const FName AMyAIController::bCanAttackKey(TEXT("bCanAttack"));

AMyAIController::AMyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject
	(TEXT(" / Script / AIModule.BlackboardData'/Game/Enemy/Type_HumanBoard.Type_HumanBoard'"));
	if (BBObject.Succeeded())
		BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject
	(TEXT("/Script/AIModule.BehaviorTree'/Game/Enemy/Type_HumanTree.Type_HumanTree'"));
	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;

	SetPerceptionSystem();
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	GetBlackboardComponent()->SetValueAsBool(bCanAttackKey, true);
	
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

 }

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void AMyAIController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	AAiTestSampleCharacter* player = Cast<AAiTestSampleCharacter>(actor);
	if (nullptr != player)
	{
		//성공적으로 감지하면 블랙보드에 true값을 넣어준다.
		Blackboard->SetValueAsBool(bCanSeePlayerKey, Stimulus.WasSuccessfullySensed());
		Blackboard->SetValueAsObject(TargetActorKey, UGameplayStatics::GetPlayerPawn(this,0));
	}
}

void AMyAIController::DeadAI()
{
	AAiCharacter* OwnningPawn = Cast<AAiCharacter>(GetPawn());
	UAi_AnimInstanceBase* Anim = OwnningPawn->GetAnimBase();

	GetBrainComponent()->StopLogic("");
	OwnningPawn->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Anim->Play_AnimMontage("Death");
}

void AMyAIController::HiDamageOnAI(float Damage)
{
	AAiCharacter* OwnningPawn = Cast<AAiCharacter>(GetPawn());
	UAi_AnimInstanceBase* Anim = OwnningPawn->GetAnimBase();

	if (OwnningPawn->Enemy_HP - Damage > 0)
	{
		OwnningPawn->Enemy_HP -= Damage;
		Anim->Play_AnimMontage("HitMotionMontage");
	}
	else if (OwnningPawn->Enemy_HP - Damage <= 0)
		DeadAI();
}

void AMyAIController::RunAI()
{
	UBlackboardComponent* BlackboardComp = Blackboard;
	FVector Target;
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		Blackboard->SetValueAsVector(TargetLocationKey, Target);
		RunBehaviorTree(BTAsset);
	}
}

void AMyAIController::SetPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	AiPerceptionCom = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = AILastSeenLocation;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AiPerceptionCom->SetDominantSense(*SightConfig->GetSenseImplementation());
	AiPerceptionCom->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTargetDetected);
	AiPerceptionCom->ConfigureSense(*SightConfig);
}
