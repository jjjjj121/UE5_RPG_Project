// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/Equipment/W_Equipment.h"

#include "Widget/UserMenu/Equipment/W_State.h"
#include "Widget/UserMenu/Equipment/W_EquipSlot.h"
#include "Library/RPGFunctionLibrary.h"

#include "UserMenu/Inventory/ItemInstance.h"

#include "RPGGame/RPGGamePlayerState.h"

void UW_Equipment::NativeConstruct()
{
	Super::NativeConstruct();

	ARPGGamePlayerState* PlayerState = URPGFunctionLibrary::GetPlayerState(GetWorld());
	BP_W_State->SetState(PlayerState->State);

	EquipSlotList.Add(EEquipCategoryType::MAINWEAPON, MainWeapon_Slot);
	EquipSlotList.Add(EEquipCategoryType::SUBWEAPON, SubWeapon_Slot);
	EquipSlotList.Add(EEquipCategoryType::ARROW, Arrow_Slot);
	EquipSlotList.Add(EEquipCategoryType::HEAD, Head_Slot);
	EquipSlotList.Add(EEquipCategoryType::TOP, Top_Slot);
	EquipSlotList.Add(EEquipCategoryType::PANTS, Pants_Slot);
	EquipSlotList.Add(EEquipCategoryType::GLOVES, Glove_SLot);
	EquipSlotList.Add(EEquipCategoryType::SHOES, Shoes_Slot);
	EquipSlotList.Add(EEquipCategoryType::SUBITEMS1, SubItem_Slot1);
	EquipSlotList.Add(EEquipCategoryType::SUBITEMS2, SubItem_Slot2);

}

void UW_Equipment::UpdateAllList(TMap<EEquipCategoryType, UItemInstance*> _EquipInventory)
{
	for (auto& i : _EquipInventory) {
		if (EquipSlotList.Contains(i.Key)) {
			UW_EquipSlot* TargetSlot = *EquipSlotList.Find(i.Key);
			if (TargetSlot) {
				UpdateSlot(TargetSlot, i.Value);
				//UE_LOG(LogTemp, Warning, TEXT("[UW_Equipment] : UpdateAllList"));
			}
		}
	}
}

void UW_Equipment::UpdateSlot(UW_EquipSlot* TargetSlot, UItemInstance* ItemInstance)
{
	if (ItemInstance) {
		TargetSlot->Update(ItemInstance);
		UE_LOG(LogTemp, Warning, TEXT("[UW_Equipment] : UpdateSlot"));
	}

}
