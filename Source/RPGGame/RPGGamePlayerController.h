// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerDefinition.h"

#include "Components/TimelineComponent.h"

#include "RPGGamePlayerController.generated.h"


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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnPossess(APawn* NewPawn) override;
	virtual void SetupInputComponent() override;

public:
	/*Componenet*/
	/*Inventory*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class UAC_UserMenuComponent* UserMenuComp;

#pragma region Input
private:
	void BindAction();
	void SetupInput();
	void SetupWidget();

public:
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
		void OnInteractPress(const FInputActionValue& Value);

	UFUNCTION()
	void OnInventory(const FInputActionValue& Value);

	UFUNCTION()
	void OnAttack(const FInputActionValue& Value);

	UFUNCTION()
	void OnWheelUpDown(const FInputActionValue& Value);


	void EnhancedInputMapping();


private:
	/*Wheel Type*/
	EWheelType WheelType = EWheelType::Default;

public:
	void SetWheelType(EWheelType NewType) { WheelType = NewType; }
#pragma endregion


protected:
	FTimeline Timeline;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* FloatCurve;

	FRotator CameraRotation;

public:
	UFUNCTION()
	void OnTimelineUpdate();
	UFUNCTION()
	void OnTimelineFinished();

	void RotateCameraFront();
	void StartTurnTiemline();


};
