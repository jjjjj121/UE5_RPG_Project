// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Library/PlayerEnumLibrary.h"
#include "RPGCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API URPGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	URPGCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool bJumpable = true;
	bool bLandable = false;

	EPlayerMovementType PlayerState;

private:
	void UpdateMovementProperty();
	void UpdateWalkSpeed();

protected:
	UPROPERTY(BlueprintReadOnly)
	FHitResult GroundHitResult;	

	UPROPERTY(BlueprintReadOnly)
	float GroundDistance;


public:
	float GetGroundDistance();


};
