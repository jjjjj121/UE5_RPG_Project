// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPGGame/Structs.h"
#include "MonsterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackDelegata);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitDelegata);
DECLARE_MULTICAST_DELEGATE(FOnEndDelegata);

/**
 * 
 */
UCLASS()
class RPGGAME_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonsterAnimInstance(FObjectInitializer const& object_initializer);
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

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
		class AMonster_AI* OwningCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References", Meta = (AllowprivateAccess = true))
		class UCharacterMovementComponent* MovementComponent;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;

private:
	void UpdateAnimProperty();


	//Attack Animation
public:
	UPROPERTY()
	class UAttackBehavior* AttackBehavior;

	UPROPERTY()
	class UMonsterData* BehaviorData;

	//Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMonsterAnim MonsterAnimation;
public:
	FOnNextAttackDelegata OnNextAttack;
	FOnAttackHitDelegata OnAttackHit;
	FOnEndDelegata OnEnd;

public:
	void PlayAttackMontage();
	/*Change Montage Section*/
	void JumpToAttackMontageSection(int32 NewSection);
	/*Get Montage Section Name*/
	FName GetAttackMontageSectionName(int32 Section);

	bool IsMontagePlaying();

	int32 GetMaxCombo();
private:
	//Notify Function
	//충돌 처리 함수
	UFUNCTION()
		void AnimNotify_AttackHitNotify();
	//Combo 실행 함수
	UFUNCTION()
		void AnimNotify_NextAttackNotify();

	//End Montage Notify -> Combo 시 Animation이 중단되지 않고 진행됨
	UFUNCTION()
		void AnimNotify_EndNotify();

public:
	void SetAnimationProperty(FMonsterAnim MonsterAnimation_);

public:
	bool TurningNotify;

};
