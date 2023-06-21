// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnumHeader.h"
#include "RPGGameAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API URPGGameAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	float CurDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	FVector Velocity;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	bool SholdMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	bool IsFaliing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	EWeaponEnum WeaponEnum;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
	class ARPGGameCharacter* OwningCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
	class UCharacterMovementComponent* MovementComponent;

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

public:
	void UpdateAnimProperty();
	void UpdateIsPawnFalling();
	void UpdateWeapon();

};
