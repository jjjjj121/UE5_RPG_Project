// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/Inventory/W_Inventory.h"
#include "Widget/UserMenu/Inventory/W_InventorySlot.h"

#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Library/RPGFunctionLibrary.h"
#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"

#include "RPGGame/RPGGamePlayerController.h"
#include "UserMenu/AC_UserMenuComponent.h"


void UW_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	GridPanelList.Add(EItemCategoryType::MELEEWEAPONS, UGP_MeleeWeapon);
	GridPanelList.Add(EItemCategoryType::RANGEWEAPONS, UGP_RangeWeapon);
	GridPanelList.Add(EItemCategoryType::SHIELDS, UGP_Sheild);
	GridPanelList.Add(EItemCategoryType::CLOTHES, UGP_Clothes);
	GridPanelList.Add(EItemCategoryType::MATERIAL, UGP_Material);
	GridPanelList.Add(EItemCategoryType::CONSUMABLE, UGP_Comsumable);
	GridPanelList.Add(EItemCategoryType::SPECIAL, UGP_Special);

	/*Bind OnClick*/
	BT_MeleeWeapon->OnClicked.AddDynamic(this, &UW_Inventory::OnClicked_MeleeWeapon);
	BT_RangeWeapon->OnClicked.AddDynamic(this, &UW_Inventory::OnClicked_RangeWeapon);
	BT_Shields->OnClicked.AddDynamic(this, &UW_Inventory::OnClicked_Shields);
	BT_Clothes->OnClicked.AddDynamic(this, &UW_Inventory::OnClicked_Clothes);
	BT_Material->OnClicked.AddDynamic(this, &UW_Inventory::OnClicked_Material);
	BT_Consumable->OnClicked.AddDynamic(this, &UW_Inventory::OnClicked_Consumable);
	BT_Special->OnClicked.AddDynamic(this, &UW_Inventory::OnClicked_Special);

	ShowGrid(EItemCategoryType::MELEEWEAPONS);
}

void UW_Inventory::OnClicked_MeleeWeapon() { ShowGrid(EItemCategoryType::MELEEWEAPONS); }
void UW_Inventory::OnClicked_RangeWeapon() { ShowGrid(EItemCategoryType::RANGEWEAPONS); }
void UW_Inventory::OnClicked_Shields() { ShowGrid(EItemCategoryType::SHIELDS); }
void UW_Inventory::OnClicked_Clothes() { ShowGrid(EItemCategoryType::CLOTHES); }
void UW_Inventory::OnClicked_Material() { ShowGrid(EItemCategoryType::MATERIAL); }
void UW_Inventory::OnClicked_Consumable() { ShowGrid(EItemCategoryType::CONSUMABLE); }
void UW_Inventory::OnClicked_Special() { ShowGrid(EItemCategoryType::SPECIAL); }



void UW_Inventory::UpdateAllList(TMap<EItemCategoryType, FItemInstanceArray> _Inventory, TMap<EItemCategoryType, int32> _ListMaxNum)
{
	/*¼ÕºÁ¾ß´ï*/

	for (auto& i : _Inventory) {
		if (GridPanelList.Contains(i.Key)){
			UUniformGridPanel* TargetGrid;
			TargetGrid = *GridPanelList.Find(i.Key);
			if (TargetGrid)
			{
				UpdateList(i.Value.InstanceList, TargetGrid, *_ListMaxNum.Find(i.Key));
			}
		}
	}
}

void UW_Inventory::UpdateList(TArray<UItemInstance*> ItemList, UUniformGridPanel* TargetGrid, int32 MaxList)
{
	/*Update Item Slot*/
	for (UItemInstance* Item : ItemList) {
		if (UW_InventorySlot* InventorySlotWidget = CreateWidget<UW_InventorySlot>(GetWorld(), SlotWidgetclass)) {
			InventorySlotWidget->Update(Item);
			if (TargetGrid) {
				int32 index = TargetGrid->GetChildrenCount();
				TargetGrid->AddChildToUniformGrid(InventorySlotWidget, index / LineSlotNum, index % LineSlotNum);
				InventorySlotWidget->ParentWidget = this;
			}
		}
	}

	// Update Extra Slot
	if (MaxList)
	{
		int32 ExtraSlotNum = MaxList - TargetGrid->GetChildrenCount();
		for (int i = 0; i < ExtraSlotNum; i++){
			UW_InventorySlot* ExtraInventorySlotWidget = CreateWidget<UW_InventorySlot>(GetWorld(), SlotWidgetclass);
			if (ExtraInventorySlotWidget){
				if (TargetGrid){
					int32 index = TargetGrid->GetChildrenCount();
					TargetGrid->AddChildToUniformGrid(ExtraInventorySlotWidget, index / LineSlotNum, index % LineSlotNum);
					ExtraInventorySlotWidget->ParentWidget = this;
				}
			}
		}
	}
}

void UW_Inventory::ShowGrid(EItemCategoryType ShowGrid)
{
	for (auto Grid : GridPanelList) {
		Grid.Key == ShowGrid ? Grid.Value->SetVisibility(ESlateVisibility::Visible) : Grid.Value->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UW_Inventory::UpdateSelectItem(UItemInstance* NewItemInstance)
{
	if (NewItemInstance) {
		FItemData ItemData = NewItemInstance->ItemDefinition->GetItemData();

		IMG_ItemIcon->SetBrushFromTexture(ItemData.ItemIcon);
		TB_ItemName->SetText(FText::FromString(ItemData.ItemName));
		TB_ItemDescription->SetText(FText::FromString(ItemData.Description));
	}
	else {
		IMG_ItemIcon->SetBrushFromTexture(DefaultIcon);
		TB_ItemName->SetText(FText::FromString(TEXT("")));
		TB_ItemDescription->SetText(FText::FromString(""));
	}
}

bool UW_Inventory::RemoveItem(UItemInstance* NewItemInstance, int32 Num)
{
	if (ARPGGamePlayerController* PlayerController = URPGFunctionLibrary::GetPlayerController(GetWorld()))
	{
		if (UAC_UserMenuComponent* InventoryComponent = PlayerController->FindComponentByClass<UAC_UserMenuComponent>())
		{

			if (InventoryComponent->RemoveItemToInventory(NewItemInstance, Num))
			{
				return true;
			}
		}
	}

	return false;
}



