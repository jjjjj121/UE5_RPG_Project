// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGame/EnumHeader.h"

#include "EquipmentDefinition.generated.h"

class AEquipmentActor;
class UEquipmentInstance;

/**
 * 
 */

USTRUCT()
struct FEquipmentActorToSpawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<AEquipmentActor> ActorToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	FName AttachSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	FTransform AttachTransform;
};


UCLASS(BlueprintType, Blueprintable, Const, Abstract)
class RPGGAME_API UEquipmentDefinition : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<UEquipmentInstance> InstanceType;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	FEquipmentActorToSpawn ActorToSpawn;

};
