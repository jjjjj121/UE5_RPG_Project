// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"
#include "ItemFragment_Consume.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UItemFragment_Consume : public UItemFragment
{
	GENERATED_BODY()
	
public:
	virtual bool OnUseItem(UItemInstance* _Instance) const override;

};
 