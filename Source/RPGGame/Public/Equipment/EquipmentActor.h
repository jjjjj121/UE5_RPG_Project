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

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UMeshComponent* TEST;

	UPROPERTY(EditAnywhere)
	bool IsRootSkeletal;

public:
	UPROPERTY(EditAnywhere)
	FString ItemID;

public:
	AEquipmentActor();

protected:
	virtual void BeginPlay() override;

public:
	UMeshComponent* GetMesh() const;

	void SetID(FString NewID);

};
