// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnumHeader.h"
#include "Library/AnimEnumLibrary.h"
#include "Library/PlayerEnumlibrary.h"
#include "Animation/BlendSpace.h"
#include "RPGGameAnimInstance.generated.h"

//여러 함수를 동시에 실행 시킬 수 있는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnNextAttackDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitDelegate);
DECLARE_MULTICAST_DELEGATE(FOnChargeAttackDelegate);
DECLARE_MULTICAST_DELEGATE(FOnEndRollDelegate);

class UBehaviorAnimData;

UCLASS()
class RPGGAME_API URPGGameAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

#pragma region Property

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	float GroundDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character_State_Data", Meta = (AllowprivateAccess = true))
	bool IsFight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character_State_Data", Meta = (AllowprivateAccess = true))
	bool IsGuard;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement_Data", Meta = (AllowprivateAccess = true))
	FVector2D InputVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation_Data")
	float CurrentDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OverlayType")
	EOverlayType OverlayType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OverlayType")
	EPlayerMovementType StateType;



public:
	float LandableDistance;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
	class ARPGGameCharacter* OwningCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
	class URPGCharacterMovementComponent* MovementComponent;

public:
	void SetIsFight(bool NewFightStance) { IsFight = NewFightStance; }

	float GetGroundDistance() { return GroundDistance; }

#pragma endregion

protected:
	URPGGameAnimInstance(FObjectInitializer const& object_initializer);

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

public:
	void PlayMontage(UAnimMontage* NewMontage, float Newrate = 1.f);
	void PlayMontage_Section(UAnimMontage* NewMontage, FName NewSectionName);

#pragma region Attack

public:
	bool bLandable = false;

public:
	FOnNextAttackDelegate OnNextAttack;
	FOnAttackHitDelegate OnAttackHit;
	FOnChargeAttackDelegate OnChargeAttack;
	FOnEndRollDelegate OnEndRoll;

public:
	FName GetMontageNextSectionName(FName SectionName, int32 Section);

	void UpdateLandalbe();

private:
	//Notify Function
	//충돌 처리 함수
	UFUNCTION()
	void AnimNotify_AttackHitNotify();

	UFUNCTION()
	void AnimNotify_NextAttackNotify();

	UFUNCTION()
	void AnimNotify_ChargeAttackNotify();

	UFUNCTION()
	void AnimNotify_EndRoll();


#pragma endregion 


};
