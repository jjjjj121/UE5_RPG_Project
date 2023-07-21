// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGGame/EnumHeader.h"
#include "Item.generated.h"

UCLASS()
class RPGGAME_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		class UDataTable* ItemData;

public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	virtual void SpawnItem();
};
