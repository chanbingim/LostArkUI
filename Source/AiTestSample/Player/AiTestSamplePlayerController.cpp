// Copyright Epic Games, Inc. All Rights Reserved.

#include "AiTestSamplePlayerController.h"
#include "AiTestSampleCharacter.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter_Anim.h"
#include "../CustomUI/InventroyUIClass.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "../CustomUI/HUD_MainGame.h"
#include "../CustomUI/SkillWidgetClass.h"
#include "EnhancedInputSubsystems.h"

AAiTestSamplePlayerController::AAiTestSamplePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AAiTestSamplePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AAiTestSamplePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
		
}

void AAiTestSamplePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AAiTestSamplePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AAiTestSamplePlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AAiTestSamplePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AAiTestSamplePlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AAiTestSamplePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AAiTestSamplePlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AAiTestSamplePlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AAiTestSamplePlayerController::OnTouchReleased);

		EnhancedInputComponent->BindAction(SetAttackClickAction, ETriggerEvent::Triggered, this, &AAiTestSamplePlayerController::OnAttackTriggered);

		EnhancedInputComponent->BindAction(SetOpenSkillUI, ETriggerEvent::Triggered, this, &AAiTestSamplePlayerController::OnOpenSkillUiTriggered);
		EnhancedInputComponent->BindAction(SetEvasionAction, ETriggerEvent::Triggered, this, &AAiTestSamplePlayerController::OnSetEvansionTriggered);
		EnhancedInputComponent->BindAction(SetOpenInventroy, ETriggerEvent::Triggered, this, &AAiTestSamplePlayerController::OnOpenInventroyTriggered);
	}
}

void AAiTestSamplePlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AAiTestSamplePlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;

	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	UWidget* selectWidget = Cast<UWidget>(Hit.GetActor());
	// If we hit a surface, cache the location
	if (bHitSuccessful && selectWidget == nullptr)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AAiTestSamplePlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

void AAiTestSamplePlayerController::OnAttackTriggered()
{
	FHitResult Hit;
	AAiTestSampleCharacter* CurrentPlayer = Cast<AAiTestSampleCharacter>(GetPawn());

	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	FVector Dir = Hit.Location - CurrentPlayer->GetActorLocation();

	CurrentPlayer->SetActorRotation(Dir.ToOrientationQuat() * -1.f);
	CurrentPlayer->NotrmalAttackPlayer();
	
}

void AAiTestSamplePlayerController::OnOpenSkillUiTriggered()
{
	AHUD_MainGame* MainHUD = Cast<AHUD_MainGame>(GetHUD());
	USkillWidgetClass*SkillWidget = Cast<USkillWidgetClass>(MainHUD->Find_Widget(EWidgetName::WD_SkillUI));

	if (SkillWidget->GetVisibility() != ESlateVisibility::Collapsed)
	{
		SkillWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
		SkillWidget->SetVisibility(ESlateVisibility::Visible);
}

// Triggered every frame when the input is held down
void AAiTestSamplePlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AAiTestSamplePlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AAiTestSamplePlayerController::OnSetEvansionTriggered()
{
	AAiTestSampleCharacter* OwnningPawn = Cast<AAiTestSampleCharacter>(GetPawn());
	UPlayerCharacter_Anim* PawnAnim = Cast<AAiTestSampleCharacter>(GetPawn())->GetAnimInstance();
	
	if (bMoveEvansion)
		return;

	StopMovement();
	PawnAnim->Play_AnimMontage("Evansion");
}

void AAiTestSamplePlayerController::OnOpenInventroyTriggered()
{
	AHUD_MainGame* MainHUD = Cast<AHUD_MainGame>(GetHUD());
	UInventroyUIClass* InventroyWidget = Cast<UInventroyUIClass>(MainHUD->Find_Widget(EWidgetName::WD_Inventory));

	if (nullptr == InventroyWidget)
		return;

	if (InventroyWidget->GetVisibility() != ESlateVisibility::Collapsed)
	{
		InventroyWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
		InventroyWidget->SetVisibility(ESlateVisibility::Visible);
}
