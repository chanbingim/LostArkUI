// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class AMyAIController : public AAIController
{
	GENERATED_BODY()

	AMyAIController();
private :
	UPROPERTY(EditAnywhere, Category = "AITree")
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere, Category = "AITree")
	class UBlackboardData* BBAsset;

	UPROPERTY(VisibleAnywhere, Category = AI)
	TObjectPtr<UAIPerceptionComponent> AiPerceptionCom = nullptr;

	TObjectPtr<class UAISenseConfig_Sight> SightConfig = nullptr;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
public:
	static const FName TargetLocationKey;
	static const FName bCanSeePlayerKey;
	static const FName HomePosKey;
	static const FName TargetActorKey;
	static const FName bCanAttackKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AISightRadius = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AILoseSightRadius = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AIFieldOfView = 90.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AISightAge = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AILastSeenLocation = 900.f;

	UFUNCTION(BlueprintCallable)
	void DeadAI();

	UFUNCTION(BlueprintCallable)
	void HiDamageOnAI(float Damage);

	UFUNCTION()
	void RunAI();

	UFUNCTION()
	void SetPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const Stimulus);
};
