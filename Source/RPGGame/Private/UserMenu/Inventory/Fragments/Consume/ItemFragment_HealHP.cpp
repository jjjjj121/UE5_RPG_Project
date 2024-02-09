// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMenu/Inventory/Fragments/Consume/ItemFragment_HealHP.h"

#include "Library/RPGFunctionLibrary.h"

#include "RPGGame/RPGGamePlayerState.h"

bool UItemFragment_HealHP::OnUseItem(UItemInstance* _Instance) const
{
	if (_Instance) {
		
		FItemData ItemData = _Instance->ItemDefinition->GetItemData();

		ARPGGamePlayerState* PlayerState = URPGFunctionLibrary::GetPlayerState(_Instance);
		
		PlayerState->UpdateHP(ItemData.ModifierValue);


		return true;
	}

	return false;
}
