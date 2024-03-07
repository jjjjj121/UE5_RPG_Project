// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "RPGGame/EnumHeader.h"
#include "W_Equipment.generated.h"

class UW_EquipSlot;
class UItemInstance;
class UEquipmentInstance;
struct FItemInstanceArray;
struct FEquipmentList;

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_Equipment : public URPGUserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TMap<EEquipCategoryType, UW_EquipSlot*> EquipSlotList;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* MainWeapon_Slot;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* SubWeapon_Slot;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* Arrow_Slot;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* Head_Slot;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* Top_Slot;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* Pants_Slot;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* Glove_SLot;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* Shoes_Slot;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* SubItem_Slot1;

	UPROPERTY(BlueprintReadOnly, Category = "Equip Slot", meta = (BindWidget))
		UW_EquipSlot* SubItem_Slot2;

	/*State*/
	UPROPERTY(BlueprintReadOnly, Category = "State", meta = (BindWidget))
		class UW_State* BP_W_State;

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateAllList(FEquipmentList _EquipInventory);
	void UpdateSlot(UW_EquipSlot* TargetSlot, UEquipmentInstance* EquipInstance);

};
