// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidgetBase.h"
#include "RPGGame/Structs.h"
#include "W_RootItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_RootItemSlot : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
		class UTextBlock* TB_ItemName;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
		class UTextBlock* TB_ItemNum;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
		class UBorder* B_Select;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
		class UBorder* B_ItemGrade;

public:
	FItemData ItemData;

public:
	void SetItemData(FItemData NewData);
};
