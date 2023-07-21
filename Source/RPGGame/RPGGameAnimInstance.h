// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnumHeader.h"
#include "RPGGameAnimInstance.generated.h"

//여러 함수를 동시에 실행 시킬 수 있는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnNextAttackDelegata);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitDelegata);

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
	bool ShouldMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	bool IsFaliing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	EWeaponType WeaponEnum;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
	class ARPGGameCharacter* OwningCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
	class UCharacterMovementComponent* MovementComponent;

protected:
	URPGGameAnimInstance(FObjectInitializer const& object_initializer);

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

public:
	void UpdateAnimProperty();
	void UpdateIsPawnFalling();
	void UpdateWeapon();

	//Attack Animation
public:
	UPROPERTY(EditAnywhere)
	class UAttackBehavior* AttackBehavior;


public:
	FOnNextAttackDelegata OnNextAttack;
	FOnAttackHitDelegata OnAttackHit;

public:
	void PlayAttackMontage();
	/*Change Montage Section*/
	void JumpToAttackMontageSection(int32 NewSection);
	/*Get Montage Section Name*/
	FName GetAttackMontageSectionName(int32 Section);

	UFUNCTION()
	int32 GetMaxCombo();
private:
	//Notify Function
	//충돌 처리 함수
	UFUNCTION()
		void AnimNotify_AttackHitNotify();
	//Combo 실행 함수
	UFUNCTION()
		void AnimNotify_NextAttackNotify();

public:
	void SetBehavior(TSubclassOf<UAttackBehavior> Behavior);

};
