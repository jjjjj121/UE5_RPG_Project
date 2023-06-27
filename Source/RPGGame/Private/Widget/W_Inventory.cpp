// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/W_Inventory.h"
#include "Components/UniformGridPanel.h"
#include "Widget/W_InventorySlot.h"

void UW_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	InitInventory();

}

void UW_Inventory::InitInventory()
{
	if (SlotWidgetclass) {

		for (int i = 0; i < 33; ++i) {
			if (UW_InventorySlot* InventorySlot = Cast<UW_InventorySlot>(CreateWidget(GetWorld(), SlotWidgetclass))) {
				UGP_Inventory->AddChildToUniformGrid(InventorySlot, CurRow, CurColumn);
				++CurColumn;
				if (CurColumn >= 11) {
					CurColumn = 0;
					++CurRow;
					//UE_LOG(LogTemp, Warning, TEXT("NUM"));
				}
			}
		}

	}
	CurColumn = 0, CurRow = 0;

	//UE_LOG(LogTemp, Warning, TEXT("INIT INVENTORY"));
}
