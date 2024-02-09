// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class ARPGGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGGAME_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TWeakObjectPtr<ARPGGameCharacter> OwnerPlayer;

private:
	void UpdateSensing();
	void UpdateUI();

protected:
	float SensingRadius;

private:
	TWeakObjectPtr<AActor> TargetActor;

	FCollisionShape CollisionShape;
	FCollisionQueryParams CQParams;
	
public:
	TWeakObjectPtr<AActor> GetTargetActor() { return TargetActor; }

#pragma region Interaction
public:
	UFUNCTION(BlueprintPure)
		bool CanInteraction() const;

	UFUNCTION(BlueprintCallable)
		bool ExecuteInteraction(UItemInstance* NewItemInstance);

	UFUNCTION(BlueprintCallable)
		void StopInteraction();

#pragma endregion
};
