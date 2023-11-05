// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidgetBase.h"
#include "RPGGame/Structs.h"
#include "W_Inventory.generated.h"

/**
 *
 */
UCLASS()
class RPGGAME_API UW_Inventory : public URPGUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	class UUniformGridPanel* UGP_Inventory;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> SlotWidgetclass;

	TMap<int32, class UW_InventorySlot*> InventorySlotList;

public:
	int32 CurRow = 0;
	int32 CurColumn = 0;

public:
	void NativeConstruct() override;

public:
	void InitInventory();
	void AddItem(FItemData ItemData);
};
