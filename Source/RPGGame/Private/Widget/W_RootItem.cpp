// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/W_RootItem.h"
#include "Widget/W_RootItemSlot.h"
#include "Components/ScrollBox.h"

void UW_RootItem::ActiveList()
{
	if (SlotWidgetclass && RootItems.Num()) {
		for (AItem* Item : RootItems) {
			if (UW_RootItemSlot* RootItemSlot = Cast<UW_RootItemSlot>(CreateWidget(GetWorld(), SlotWidgetclass))) {
				
				SB_RootItemList->AddChild(RootItemSlot);
				//RootItemSlot->SetItemData();
			}
		}
	}
}
