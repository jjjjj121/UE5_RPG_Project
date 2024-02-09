// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/DataTableManager.h"

FItemTable* UDataTableManager::GetItemData(FString ItemDataID)
{
	if (ensure(ItemDataTable) == false)
		return nullptr;

	const FString ContextStr = TEXT("ItemDataTable");
	
	FItemTable* ItemData = ItemDataTable->FindRow<FItemTable>(*ItemDataID, ContextStr);

	if (ensureMsgf(ItemData, TEXT("[UDataTableManager::GetItemData] Non Item Data"))) {
		return ItemData;
	}

	return nullptr;
}

TSubclassOf<UUserWidget> UDataTableManager::GetWidgetClassWithName(FName WidgetName)
{
	if (ensure(WidgetDataTable) == false) {
		return nullptr;
	}

	const FString ContextStr = TEXT("WidgetDataTable");
	FWidgetData* WidgetData = WidgetDataTable->FindRow<FWidgetData>(WidgetName, ContextStr);

	if (ensureMsgf(WidgetData, TEXT("[UDataTableManager::GetItemData] Non Widget Data"))) {
		return WidgetData->WidgetClass;
	}

	return nullptr;
}
