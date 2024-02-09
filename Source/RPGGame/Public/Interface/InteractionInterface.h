// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGGame/Structs.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGGAME_API IInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	bool IsAvailableInteraction() const;

	UFUNCTION(BlueprintNativeEvent)
	void IsShowIcon();

	UFUNCTION(BlueprintNativeEvent)
	bool ExecuteInteraction(AActor* InteractionTarget, UItemInstance* NewItemInstance);

	UFUNCTION(BlueprintNativeEvent)
	void StopInteration(AActor* InteractionTarget);

	UFUNCTION(BlueprintNativeEvent)
	void SetTouchActor(AActor* NewTouchActor);

	UFUNCTION(BlueprintNativeEvent)
	TArray<class UItemInstance*> GetRootItemList();

	UFUNCTION(BlueprintNativeEvent)
	FName GetInteractionActorName();

	UFUNCTION(BlueprintNativeEvent)
	FVector GetInteractionWidgetLocation();


	class ARPGGameCharacter* TouchActor;
};
