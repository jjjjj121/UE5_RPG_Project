// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserMenu/Inventory/ItemDefinition.h"
#include "ItemFragment_Equipment.generated.h"

class UItemInstance;

/**
 * 
 */
UCLASS()
class RPGGAME_API UItemFragment_Equipment : public UItemFragment
{
	GENERATED_BODY()
	
public:
	UItemFragment_Equipment();

	float TestNUm;
public:
	virtual bool OnUseItem(UItemInstance* _Instance) const override;

};
