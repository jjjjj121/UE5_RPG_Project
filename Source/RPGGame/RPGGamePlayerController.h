// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerDefinition.h"
#include "RPGGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API ARPGGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARPGGamePlayerController();

private:
	/*시작 시 추가되는 위젯들*/
	TArray<FName> BaseWidgetName;

	class ARPGGameCharacter* PossessedPlayer;

	class ARPGGameHUD* HUD;

protected:


public:
	virtual void OnPossess(APawn* NewPawn) override;
	virtual void SetupInputComponent() override;

public:
	/*Componenet*/
	/*Inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class UAC_InventoryComponent* Inventory;

#pragma region Input
private:
	void BindAction();
	void SetupInput();
	void SetupWidget();

protected:
	/** Interation Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InteractAction;

	/** Inventory Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InventoryAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* AttackAction;

	/** List Up Down Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* ListUpDownAction;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "RPG|Input")
		class UInputMappingContext* InputMappingContext;

protected:
	UFUNCTION()
		void OnInteract(const FInputActionValue& Value);

	UFUNCTION()
	void OnInventory(const FInputActionValue& Value);

	UFUNCTION()
	void OnAttack(const FInputActionValue& Value);

	UFUNCTION()
	void OnWheelUpDown(const FInputActionValue& Value);


	void EnhancedInputMapping();


public:
	/*Wheel Type*/
	EWheelType WheelType = EWheelType::Default;
#pragma endregion

};
