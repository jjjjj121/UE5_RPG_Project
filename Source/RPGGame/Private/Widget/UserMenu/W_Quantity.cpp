// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/W_Quantity.h"


#include "Widget/UserMenu/W_RButtonMenu.h"
#include "Widget/UserMenu/Inventory/W_InventorySlot.h"

#include "UserMenu/Inventory/ItemInstance.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"



void UW_Quantity::NativeConstruct()
{
	BT_Accept->OnClicked.AddDynamic(this, &UW_Quantity::OnClicked_Accept);
	BT_Cancel->OnClicked.AddDynamic(this, &UW_Quantity::OnClicked_Cancel);
}

void UW_Quantity::OnClicked_Accept()
{
	if (ETB_Quantity->GetText().IsNumeric()) {
		UE_LOG(LogTemp, Warning, TEXT("[UW_Quantity] : Accept %s"), *ETB_Quantity->GetText().ToString());

		int32 Num = FCString::Atoi(*ETB_Quantity->GetText().ToString());

		if (Num > 0 && Num <= TargetSlot->ItemInstance->ItemStack) {
			TargetSlot->ThrowAwayItem(Num);
			this->RemoveFromParent();
		}
	}
	
}

void UW_Quantity::OnClicked_Cancel()
{
	UE_LOG(LogTemp, Warning, TEXT("[UW_Quantity] : Cancel"));
	this->RemoveFromParent();
}

