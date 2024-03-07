// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "RPGGame/Structs.h"
#include "W_InventorySlot.generated.h"

class UItemInstance;
class UButton;
class UW_Inventory;
/**
 * 
 */
UCLASS()
class RPGGAME_API UW_InventorySlot : public URPGUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
	UButton* BT_ItemButton;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
	class UImage* IMG_Item;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
	class UTextBlock* TB_Stack;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
	class UBorder* B_ItemGrade;

public:
	UItemInstance* ItemInstance;

	UW_Inventory* ParentWidget;

protected:
	virtual void NativeConstruct() override;

public:
	void SetItemGrade(EItemGrade Grade);
	void ThrowAwayItem(int32 Num = 1);
	bool RemoveItem(int32 Num = 1);

public:
	virtual void Update(UItemInstance* NewItem);
	virtual void UseItem();
	virtual void EquipItem();
	virtual void UnEquipItem() {};

private:
	UFUNCTION()
	virtual void OnClicked_Item();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
