// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

private:
	UAnimMontage* AttachAnimData;

public:	
	UPlayerCombatComponent();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region LockOn
private:
	AActor* Target;

	float LimitDistance;


public:
	void ActiveLockon();


#pragma endregion
public:


};
