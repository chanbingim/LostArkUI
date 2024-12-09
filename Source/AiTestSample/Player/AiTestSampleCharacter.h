// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AiTestSampleCharacter.generated.h"

UCLASS(Blueprintable)
class AAiTestSampleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAiTestSampleCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PLAYERINFO")
	float Max_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PLAYERINFO")
	float Max_MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PLAYERINFO")
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAttack")
	int32 NormalAttackCombo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerAttack")
	bool bIsCanNextCombo = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsComboInputOn = false;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	UFUNCTION()
	void GetDamage(float Damage);

	UFUNCTION()
	void NotrmalAttackPlayer();

	UFUNCTION()
	void OnMontageAttackCheck();

	UFUNCTION()
	void DeathPlayer();

	UFUNCTION()
	void OnAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Top down camera */
	

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UPlayerCharacter_Anim* AnimInstance = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PLAYERINFO", meta = (AllowPrivateAccess = "true"))
	float Current_HP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PLAYERINFO", meta = (AllowPrivateAccess = "true"))
	float Current_MP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerAttack", meta = (AllowPrivateAccess = "true"))
	int32 NormalMaxAttackCombo = 3;

public :
	UPlayerCharacter_Anim* GetAnimInstance() { return AnimInstance; }
};

