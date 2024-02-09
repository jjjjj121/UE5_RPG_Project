// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMenu/Inventory/Fragments/ItemFragment_Equipment.h"

#include "Library/RPGFunctionLibrary.h"
#include "RPGGame/EnumHeader.h"

#include "RPGGame/RPGGamePlayerController.h"
#include "Equipment/EquipmentDefinition.h"
#include "UserMenu/Inventory/ItemInstance.h"

#include "System/RPGGameInstance.h"

#include "UserMenu/AC_UserMenuComponent.h"

UItemFragment_Equipment::UItemFragment_Equipment()
{
	UE_LOG(LogTemp, Warning, TEXT("UItemFragment_Equipment : Construct"));

	TestNUm = 10.f;
}

bool UItemFragment_Equipment::OnUseItem(UItemInstance* _Instance) const
{

	if (_Instance) {
		//FItemData ItemData = _Instance->ItemDefinition->GetItemData();

		if (ARPGGamePlayerController* Controller = URPGFunctionLibrary::GetPlayerController(_Instance)) {
			if (UAC_UserMenuComponent* UserMenuComponent = Controller->FindComponentByClass<UAC_UserMenuComponent>()){


				FItemTable* ItemTable = RPG_GAMEINSTANCE(_Instance)->GetDataTableManager()->GetItemData(_Instance->ItemID);
				UEquipmentDefinition* EquipDef = Cast<UEquipmentDefinition>(ItemTable->EquipDef->GetDefaultObject());

				UserMenuComponent->EquipItem(EquipDef, _Instance);
			}
		}
		
		return true;
	}

	return false;

}