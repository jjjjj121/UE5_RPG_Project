// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Library/AnimEnumLibrary.h"
#include "PlayerCombatComponent.generated.h"

class UBehaviorAnimData;
class ARPGGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGGAME_API UPlayerCombatComponent : public UActorComponent
{
	GENERATED_BODY()


private:
	UPROPERTY()
	ARPGGameCharacter* OwningActor;

	UPROPERTY(EditAnywhere)
	class URPGGameAnimInstance* AnimInstance;

private:
	UAnimMontage* AttachAnimData;

	FAnimMontageSet WeaponMontageset;


public:	
	UPlayerCombatComponent();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	void SetWeaponMontageset(FAnimMontageSet NewMontageSet) { WeaponMontageset = NewMontageSet; }
	void PlayMontageWithBind(UAnimMontage* NewMontage);

#pragma region Attack

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
	bool IsComboInputOn;

	bool bFullCharged;

	bool bDoOnce = true;

private:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void JumpAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnNextAttack();

	/*Start Combo -> Set Property*/
	void AttackStartComboState();
	/*End Combo -> Init Property*/
	void AttackEndComboState();

	int32 GetMaxCombo();

public:
	void Charging();
	void ChargingAttack();
	void LightAttack();
	void MeleeJumpAttack();
	void DodgeAttack();
	void RollAttack();

	void Attack(bool IsPressed);

	bool GetIsAttacking() { return IsAttacking; }

	void TurnAttack();

#pragma endregion



#pragma region Guard

private:
	
	bool bIsGuard = false;


public:
	void ActivateGuard();
	void DeactivateGuard();

public:
	bool GetIsGuard() { return bIsGuard; }

#pragma endregion

#pragma region LockOn
private:
	AActor* Target;

	float LimitLockOnDistance;
	float LimitUnLockDistance;

	bool bIsLockedOn = false;


public:
	void ActivateLockon();
	void DeactivateLockon();

public:
	bool GetLockedOn() { return bIsLockedOn; }

#pragma endregion
public:


};
