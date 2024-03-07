// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnumHeader.h"
#include "PlayerDefinition.h"
#include "Library/PlayerEnumLibrary.h"
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

	/** Equip Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EquipAction;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class ARPGGameHUD* HUD;

	UPROPERTY(EditDefaultsOnly)
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly ,Meta = (AllowprivateAccess = true))
	class UPlayerCombatComponent* CombatComponent;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimLayer", Meta = (AllowprivateAccess = true))
	TSubclassOf<UAnimInstance> DefaultAnimLayer;

	EPlayerMovementType MovementType;

public:
	void SetAnimLayer(TSubclassOf<UAnimInstance> NewAnimLayer);

public:
	UInteractionComponent* GetinteractionComponent() { return InteractionComponent; }

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

	/** Called for Sprint input */
	UFUNCTION()
	void OnEquip(const FInputActionValue& Value);


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
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Animation", Meta = (AllowprivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(EditAnywhere)
	class URPGGameAnimInstance* AnimInstance;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/*Start Combo -> Set Property*/
	void AttackStartComboState();
	/*End Combo -> Init Property*/
	void AttackEndComboState();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon();

	class AEquipItem* Weapon;

public:
	void Attack();
	bool GetIsAttacking();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHP(float MaxHP, float CurHP);

	UFUNCTION(BlueprintImplementableEvent)
	void ReceivingDamage(float MaxHP, float CurHP);


	int32 CalculateDirectionIndex(float Direction);

	UPROPERTY(EditAnywhere)
	TMap<int32, UAnimMontage*> Basic_Hit_Reaction_Montages;

	UPROPERTY(EditAnywhere)
	TMap<int32, UAnimMontage*> Charged_Hit_Reaction_Montages;

	UPROPERTY(EditAnywhere)
	TMap<int32, UAnimMontage*> Death_Reaction_Montages;

	UFUNCTION(BlueprintCallable)
	void DoDeath(int32 DirectionIndex);

	float GetDamage();

	void TurnAttack();

#pragma endregion

public:
	//UPROPERTY(BlueprintReadWrite, Category = "Stance")
	//bool IsFight;
	//
	//void SetFightStance(bool NewStance);

	//FTimerHandle OnFightTimerHandle;

	//UPROPERTY(BlueprintReadWrite)
	//EPlayerStance PlayerStance;



};

