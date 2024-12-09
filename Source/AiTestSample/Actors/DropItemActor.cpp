// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItemActor.h"
#include "../MyGameInstance.h"
#include "ActorsDataTable/ActorDataTableBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ADropItemActor::ADropItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMeshComponents"));
	ActorMesh->SetupAttachment(CollisionBox);
}

// Called when the game starts or when spawned
void ADropItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	FString DataRowName = FString::FromInt(Item_DataID);
	FItemDataRow* itemData = GameInstance->ItemDataTable->FindRow<FItemDataRow>(FName(DataRowName), "");

	Item_Type = itemData->ItemType;
	ActorMesh->SetStaticMesh(itemData->ItemStaticMesh);
}

// Called every frame
void ADropItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}