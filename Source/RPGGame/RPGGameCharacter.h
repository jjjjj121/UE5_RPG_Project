// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "EnumHeader.h"
#include "Library/AnimEnumLibrary.h"
#include "Library/PlayerEnumLibrary.h"

#include "PlayerDefinition.h"
#include "RPGGameCharacter.generated.h"

class UInteractionComponent;


UCLASS(config = Game)
class ARPGGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Crouch Input Action */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputAction* CrouchAction;

	/** Walk Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* WalkAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RollAction;

	/** Equip Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EquipAction;

	/** Guard Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* GuardAction;

	/** LockOn Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LockOnAction;


	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ARPGGameHUD* HUD;

	UPROPERTY(EditDefaultsOnly)
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly ,Meta = (AllowprivateAccess = true))
	class UPlayerCombatComponent* CombatComponent;


private:
	/*Default Animation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimLayer", Meta = (AllowprivateAccess = true))
	TSubclassOf<UAnimInstance> DefaultAnimLayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimLayer", Meta = (AllowprivateAccess = true))
	FAnimMontageSet DefaultAnimMontageSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimLayer", Meta = (AllowprivateAccess = true))
	TMap<FName, UAnimMontage*> DeathReact;

	EPlayerMovementType MovementType;

	EPlayerStateType PlayerState;

public:
	FVector2D LocalInputVector;

public:
	void SetAnimData(TSubclassOf<UAnimInstance> NewAnimLayer, FAnimMontageSet NewMontageSet);

public:
	UInteractionComponent* GetinteractionComponent() { return InteractionComponent; }

	UPlayerCombatComponent* GetCombatComponent() { return CombatComponent; }
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", Meta = (AllowprivateAccess = true))
	EWeaponType WeaponEnum;

	AActor* RootingActor;

	UPROPERTY(BlueprintReadOnly)
	bool IsDead = false;

public:
	ARPGGameCharacter(const class FObjectInitializer& ObjectInitializer);

	/*Input*/
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Crouch input */
	//UFUNCTION()
	//void OnCrouch(const FInputActionValue& Value);

	/** Called for Walk input */
	UFUNCTION()
	void OnWalk(const FInputActionValue& Value);

	/** Called for Sprint input */
	UFUNCTION()
	void OnSprint(const FInputActionValue& Value);

	/** Called for Roll input */
	UFUNCTION()
	void OnRoll(const FInputActionValue& Value);

	/** Called for Equip input */
	UFUNCTION()
	void OnEquip(const FInputActionValue& Value);

	/** Called for Guard input */
	UFUNCTION()
	void OnGuard(const FInputActionValue& Value);

	/** Called for LockOn input */
	UFUNCTION()
	void OnLockOn(const FInputActionValue& Value);


	UFUNCTION()
	void OnJump();

	void EnhancedInputMapping();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	//Apply Damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

#pragma region Attack & React

	/*Animation*/
private:
	UPROPERTY(EditAnywhere)
	class URPGGameAnimInstance* AnimInstance;

public:
	URPGGameAnimInstance* GetAnimInstance() { return AnimInstance; }

public:
	void Attack(bool IsPressed);
	void Charging();
	//bool GetIsAttacking();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHP(float MaxHP, float CurHP);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceivingDamage(float MaxHP, float CurHP);


	FName ConvertDirection(float Direction);


	UFUNCTION(BlueprintCallable)
	void DoDeath(FName DirectionIndex);

	float GetDamage();

#pragma endregion

public:



};

