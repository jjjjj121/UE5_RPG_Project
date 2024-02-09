// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserMenu/Inventory/Fragments/ItemFragment_Consume.h"
#include "ItemFragment_HealHP.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UItemFragment_HealHP : public UItemFragment_Consume
{
	GENERATED_BODY()
	
public:
	virtual bool OnUseItem(UItemInstance* _Instance) const override;
};
