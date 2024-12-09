// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Montage/MontageInterface.h"
#include "AiCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class AAiCharacter : public ACharacter, public IMontageInterface
{
	GENERATED_BODY()

private:
	// Sets default values for this character's properties
	AAiCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ANI", meta = (AllowPrivateAccess = true))
	class UAi_AnimInstanceBase* MyAnimInstance;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Attack_Check() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetWalkSpeed(float Speed);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	float Enemy_HP;

	UFUNCTION()
	void AI_Attack();

	UAi_AnimInstanceBase* GetAnimBase() { return MyAnimInstance; }
	FOnAttackEndDelegate FOnAttackEnd;
};
