// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"

#include "System/RPGGameInstance.h"


UItemInstance::UItemInstance()
{
	//ItemDefinition = CreateDefaultSubobject<UItemDefinition>(TEXT("Definition"));
}

void UItemInstance::InitInstance(FString ID)
{
	ItemID = ID;
	FItemTable* ItemTable = DATATABLE_MANAGER(GetWorld())->GetItemData(ItemID);
	ItemDefinition = ItemTable->ItemDef.GetDefaultObject();

	//ItemDefinition->SetItemData(ItemData);
}
