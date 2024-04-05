// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnumHeader.h"
#include "Library/AnimEnumLibrary.h"
#include "Animation/BlendSpace.h"
#include "RPGGameAnimInstance.generated.h"

//여러 함수를 동시에 실행 시킬 수 있는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnNextAttackDelegata);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitDelegata);

class UBehaviorAnimData;

UCLASS()
class RPGGAME_API URPGGameAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
#pragma region Property

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	EWeaponType WeaponEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	bool bEquipWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	bool bEquipShield;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion", Meta = (AllowprivateAccess = true))
	UBehaviorAnimData* DefaultAnimData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion", Meta = (AllowprivateAccess = true))
	UBehaviorAnimData* WeaponAnimData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion", Meta = (AllowprivateAccess = true))
	UBehaviorAnimData* ShieldAnimData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	float GroundDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character_State_Data", Meta = (AllowprivateAccess = true))
	bool IsFight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character_State_Data", Meta = (AllowprivateAccess = true))
	bool IsGuard;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
	class ARPGGameCharacter* OwningCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
	class UCharacterMovementComponent* MovementComponent;

public:
	void SetIsFight(bool NewFightStance) { IsFight = NewFightStance; }

#pragma endregion

protected:
	URPGGameAnimInstance(FObjectInitializer const& object_initializer);

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

public:
	void UpdateWeaponShield();
	void SetWeaponAnimData(UBehaviorAnimData* NewAnimData);
	void SetSheildAnimData(UBehaviorAnimData* NewAnimData);

	UBehaviorAnimData* GetCurBehavior();

	void PlayMontage();

#pragma region Attack
public:
	//UPROPERTY(EditAnywhere)
	//class UAttackBehavior* AttackBehavior;


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


#pragma endregion 


#pragma region Locomotion
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	UAnimationAsset* GetAnimAsset(UBehaviorAnimData* BehaviorAnimData, ELocomotionCategory LocomotionType, int32 Index = 0);

#pragma endregion


};
