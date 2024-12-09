// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropItemActor.generated.h"

UCLASS()
class AITESTSAMPLE_API ADropItemActor : public AActor
{
	GENERATED_BODY()
	
private :	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* ActorMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Collision")
	class UBoxComponent* CollisionBox = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ADropItemActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	FItemDataType Item_Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	int Item_DataID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	int Item_Count;
};
