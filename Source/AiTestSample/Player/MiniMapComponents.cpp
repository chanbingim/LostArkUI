// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapComponents.h"
#include "Camera/CameraActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values for this component's properties
UMiniMapComponents::UMiniMapComponents()
{
	Initailize();
}


// Called when the game starts
void UMiniMapComponents::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void UMiniMapComponents::Initailize()
{
	if (nullptr == GetOwner())
		return;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetOwner()->GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;

	SenceCaptureComp = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComp");
	SenceCaptureComp->SetupAttachment(GetOwner()->GetRootComponent());
	SenceCaptureComp->ProjectionType = ECameraProjectionMode::Orthographic;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>("SprtieComp");
	SpriteComp->SetupAttachment(GetOwner()->GetRootComponent());
	SpriteComp->bVisibleInSceneCaptureOnly = true;
}


