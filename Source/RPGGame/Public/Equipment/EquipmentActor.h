// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentActor.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AEquipmentActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkelMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

public:
	UPROPERTY(EditAnywhere)
	FString ItemID;

public:
	AEquipmentActor();

public:
	UMeshComponent* GetMesh() const;

};
