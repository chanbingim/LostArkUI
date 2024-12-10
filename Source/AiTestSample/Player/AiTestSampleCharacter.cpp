// Copyright Epic Games, Inc. All Rights Reserved.

#include "AiTestSampleCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Ai/AiBase/MyAIController.h"
#include "GameFramework/PlayerController.h"
#include "AiTestSamplePlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter_Anim.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "../CustomUI/HUD_MainGame.h"
#include "../CustomUI/Widget_HPbar.h"
#include "../CustomUI/PlayerStateBarClass.h"

AAiTestSampleCharacter::AAiTestSampleCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AAiTestSampleCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AAiTestSampleCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UPlayerCharacter_Anim>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AAiTestSampleCharacter::OnAttackMontageEnd);
	AnimInstance->OnAttackHitCheck.AddDynamic(this, &AAiTestSampleCharacter::OnMontageAttackCheck);

	AnimInstance->OnNextAttackCheck.AddLambda([this]()-> void
		{
			bIsCanNextCombo = false;
			if (bIsComboInputOn)
			{
				bIsCanNextCombo = true;
				bIsComboInputOn = false;
				NormalAttackCombo = FMath::Clamp<int32>(NormalAttackCombo + 1, 0, NormalMaxAttackCombo);
				AnimInstance->JumpToSectionMontage(NormalAttackCombo, "PlayerAttack");
			}
		});
}

void AAiTestSampleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	OnAttackMontageEnd(nullptr, false);
	AnimInstance->StopAllMontages(0.0f);

	Current_HP = Max_HP;
	Current_MP = Max_MP;

	AAiTestSamplePlayerController* CurrentController = Cast<AAiTestSamplePlayerController>(GetController());

	AHUD_MainGame* CurrentHUD = Cast<AHUD_MainGame>(CurrentController->GetHUD());
	UPlayerStateBarClass* Widget = Cast<UPlayerStateBarClass>(CurrentHUD->Find_Widget(EWidgetName::WD_HPBar, EWidgetType::mainWD));

	if (nullptr != Widget)
	{
		UWidget_HPbar* CurrentWidget = Cast<UWidget_HPbar>(Widget->GetHPBar());
		CurrentWidget->Dele_HPSetting.Broadcast(Current_HP, Max_HP);
		CurrentWidget->Dele_MPSetting.Broadcast(Current_MP, Max_MP);
	}
}

void AAiTestSampleCharacter::GetDamage(float Damage)
{
	if (Current_HP - Damage <= 0)
	{
		DeathPlayer();
	}

	if (Current_HP > 0)
	{
		Current_HP -= Damage;

		AAiTestSamplePlayerController* CurrentController = Cast<AAiTestSamplePlayerController>(GetController());
		AHUD_MainGame* CurrentHUD = Cast<AHUD_MainGame>(CurrentController->GetHUD());

		UPlayerStateBarClass* CurrentWidget = Cast<UPlayerStateBarClass>(CurrentHUD->Find_Widget(EWidgetName::WD_HPBar, EWidgetType::mainWD));
		UWidget_HPbar* CurrentHP = Cast<UWidget_HPbar>(CurrentWidget->GetHPBar());

		if (nullptr != CurrentHP)
		{
			CurrentHP->Dele_HPSetting.Broadcast(Current_HP, Max_HP);
		}
	}
}

void AAiTestSampleCharacter::NotrmalAttackPlayer()
{
	GetCharacterMovement()->StopActiveMovement();

	if (bIsAttacking)
	{
		if (bIsCanNextCombo)
		{
			bIsComboInputOn = true;
		}
	}
	else
	{
		bIsAttacking = true;
		bIsCanNextCombo = true;
		bIsComboInputOn = false;
		NormalAttackCombo = FMath::Clamp<int32>(NormalAttackCombo + 1, 0, NormalMaxAttackCombo);

		AnimInstance->Play_AnimMontage("PlayerAttack");
	}
}

void AAiTestSampleCharacter::DeathPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Death"));
}

void AAiTestSampleCharacter::OnAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
	NormalAttackCombo = 0;
	bIsCanNextCombo = false;
	bIsComboInputOn = false;
}

void AAiTestSampleCharacter::OnMontageAttackCheck()
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
		 AMyAIController* TargetController = Cast<AMyAIController>(OutHitResult.GetActor()->GetInstigatorController());
		 TargetController->HiDamageOnAI(10.0f);
	}
}
