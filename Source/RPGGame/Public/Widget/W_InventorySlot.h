// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidgetBase.h"
#include "RPGGame/Structs.h"
#include "W_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_InventorySlot : public URPGUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
	class UImage* IMG_Slot;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
	class UTextBlock* TB_Stack;

public:
	FItemData ItemData;

};
