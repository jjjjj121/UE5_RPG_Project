// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item.h"
#include "EquipItem.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AEquipItem : public AItem
{
	GENERATED_BODY()

public:
	AEquipItem();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* EquipTable;

public:
	virtual void BeginPlay() override;
	
private:
	void InitProperty(FName RowName);
};
