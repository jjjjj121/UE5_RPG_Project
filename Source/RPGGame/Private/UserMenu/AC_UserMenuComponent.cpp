// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMenu/AC_UserMenuComponent.h"
#include "Widget/UserMenu/W_MenuLayout.h"

#include "Library/RPGFunctionLibrary.h"
#include "Library/RPGWidgetFunctionLibrary.h"

#include "UserMenu/Inventory/ItemActor.h"
#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"

#include "Equipment/EquipmentDefinition.h"
#include "Equipment/EquipmentActor.h"

#include "RPGGame/RPGGameCharacter.h"

#include "Kismet/GameplayStatics.h"

#pragma region Inventory

UAC_UserMenuComponent::UAC_UserMenuComponent()
{

	// Inventory 최대 개수 초기화
	for (int i = 0; i < static_cast<int>(EItemCategoryType::ETC); i++)
	{
		ListMaxNum.Add(static_cast<EItemCategoryType>(i), NULL);
	}
	ListMaxNum.Add(EItemCategoryType::MELEEWEAPONS, 8);
	ListMaxNum.Add(EItemCategoryType::RANGEWEAPONS, 8);
	ListMaxNum.Add(EItemCategoryType::SHIELDS, 8);
	ListMaxNum.Add(EItemCategoryType::CLOTHES, 30);
	ListMaxNum.Add(EItemCategoryType::MATERIAL, 30);
	ListMaxNum.Add(EItemCategoryType::CONSUMABLE, 30);
	ListMaxNum.Add(EItemCategoryType::SPECIAL, 30);

	// Inventory Map 초기화
	for (int i = 0; i <= static_cast<int>(EItemCategoryType::ETC); i++) {
		FItemInstanceArray NewInstanceArray = FItemInstanceArray();
		NewInstanceArray.MaxListValue = 4;
		Inventory.Add(static_cast<EItemCategoryType>(i), NewInstanceArray);
	}

	//Equip Inventory 초기화
	for (int i = 0; i <= static_cast<int>(EEquipCategoryType::NONE); i++) {
		EquipInventory.Add(static_cast<EEquipCategoryType>(i), nullptr);
	}

}


void UAC_UserMenuComponent::ShowUserMenu(EUserMenuType MenuType)
{
	if (UW_MenuLayout* UserMenuWidget = Cast<UW_MenuLayout>(URPGWidgetFunctionLibrary::PushWidget(GetWorld(), EWidgetNames::Menu, EWidgetLayoutType::Option, EWidgetAnchorType::Fill))) {
		UserMenuWidget->InitInventory(Inventory, ListMaxNum);
		UserMenuWidget->InitEquipInventory(EquipInventory);
		UserMenuWidget->ShowMenu(MenuType);

	}

}

void UAC_UserMenuComponent::HideUserMenu()
{
	URPGWidgetFunctionLibrary::PopWidget(GetWorld(), EWidgetNames::Menu, EWidgetLayoutType::Option);
	URPGWidgetFunctionLibrary::PopWidget(GetWorld(), EWidgetNames::RButtonMenu, EWidgetLayoutType::Option);
	URPGWidgetFunctionLibrary::PopWidget(GetWorld(), EWidgetNames::Quantity, EWidgetLayoutType::Option);

	if (APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		Controller->SetInputMode(FInputModeGameOnly());
	}
}

bool UAC_UserMenuComponent::AddItemToInventory(UItemInstance* NewItemInstance) {

	UE_LOG(LogTemp, Warning, TEXT("[UAC_InventoryComponent] : AddItemToInventory"));
	if (NewItemInstance) {
		//UItemDefinition* ItemDef = Cast<UItemDefinition>(NewItemInstance->ItemDefinition.GetDefaultObject());
		FItemData ItemData = NewItemInstance->ItemDefinition->GetItemData();

		FItemInstanceArray* ItemList = Inventory.Find(ItemData.Category);

		if (ItemList->InstanceList.Num() >= ItemList->MaxListValue) { return false; }

		if (ItemList) {
			if (ItemData.IsStack) {
				for (UItemInstance* Item : ItemList->InstanceList) {
					//인벤토리에 있는 아이템인 경우
					if (Item->ItemID == NewItemInstance->ItemID) {
						Item->ItemStack += NewItemInstance->ItemStack;
						return true;
					}
				}
			}
		}
		//그 외 아이템을 새로 추가하는 경우
		/*Item 획득 Pop up 실행(해야함)*/

		ItemList->InstanceList.Add(NewItemInstance);
		return true;
	}

	return false;
}

bool UAC_UserMenuComponent::RemoveItemToInventory(UItemInstance* NewItemInstance, int32 Num)
{
	//UE_LOG(LogTemp, Warning, TEXT("[UAC_InventoryComponent] : RemoveItemToInventory"));

	if (NewItemInstance) {
		FItemData ItemData = NewItemInstance->ItemDefinition->GetItemData();

		FItemInstanceArray* ItemList = Inventory.Find(ItemData.Category);

		if (ItemList) {
			for (UItemInstance* Item : ItemList->InstanceList) {
				//인벤토리에 있는 아이템인 경우
				if (Item->ItemDefinition->GetName() == NewItemInstance->ItemDefinition->GetName()) {
					Item->ItemStack -= Num;

					if (Item->ItemStack <= 0) {
						ItemList->InstanceList.Remove(Item);
					}

					return true;
				}
			}
		}
	}

	return false;
}

#pragma endregion

#pragma region Equipment

bool UAC_UserMenuComponent::EquipItem(UEquipmentDefinition* EquipDef, UItemInstance* NewEquipItem)
{
	FItemData ItemData = NewEquipItem->ItemDefinition->GetItemData();
	bool Result = false;

	switch (EquipDef->EquipCategory)
	{
	case EEquipCategoryType::MAINWEAPON:
		if (ItemData.IsDualWield) {
			UnEquipItem(EEquipCategoryType::SUBWEAPON);
		}
		break;
	case EEquipCategoryType::SUBWEAPON:
		if (EquipInventory[EEquipCategoryType::MAINWEAPON] != nullptr) {
			FItemData MainWeaponItemData = EquipInventory[EEquipCategoryType::MAINWEAPON]->ItemDefinition->GetItemData();
			if (MainWeaponItemData.IsDualWield) {
				UnEquipItem(EEquipCategoryType::MAINWEAPON);
			}
		}
		break;
	case EEquipCategoryType::ARROW:
		break;
	case EEquipCategoryType::HEAD:
		break;
	case EEquipCategoryType::TOP:
		break;
	case EEquipCategoryType::PANTS:
		break;
	case EEquipCategoryType::GLOVES:
		break;
	case EEquipCategoryType::SHOES:
		break;
	case EEquipCategoryType::SUBITEMS1:
		break;
	case EEquipCategoryType::SUBITEMS2:
		break;
	case EEquipCategoryType::NONE:
		break;
	default:
		break;
	}

	EquipInventory[EquipDef->EquipCategory] = NewEquipItem;

	/*Item Spawn & Attach*/
	if (EquipDef->ActorToSpawn.AttachSocket != "") {
		

		AEquipmentActor* NewItem = Cast<AEquipmentActor>(GetWorld()->SpawnActorDeferred<AActor>(EquipDef->ActorToSpawn.ActorToSpawn, EquipDef->ActorToSpawn.AttachTransform));
		NewItem->ItemID = NewEquipItem->ItemID;
		NewItem->FinishSpawning(EquipDef->ActorToSpawn.AttachTransform);

		if (ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld())) {
			NewItem->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), EquipDef->ActorToSpawn.AttachSocket);

			Result = true;
		}
	}


	/*Equip Widget Update*/
	if (UW_MenuLayout* UserMenuWidget = Cast<UW_MenuLayout>(URPGWidgetFunctionLibrary::GetWidgetWithLayoutType(GetWorld(), EWidgetLayoutType::Option, EWidgetNames::Menu))) {
		UserMenuWidget->InitEquipInventory(EquipInventory);
	}



	return Result;
}

bool UAC_UserMenuComponent::UnEquipItem(EEquipCategoryType Category)
{

	UItemInstance* UnEquipInstance = *EquipInventory.Find(Category);
	if (UnEquipInstance != nullptr) {
		AddItemToInventory(UnEquipInstance);
		EquipInventory[Category] = nullptr;
	}

	return true;
}

bool UAC_UserMenuComponent::SpawnAndAttach(UItemInstance* NewEquipItem)
{
	if (NewEquipItem) {

	}
	return false;
}

bool UAC_UserMenuComponent::IsEquipWeapon()
{
	return 	EquipInventory[EEquipCategoryType::MAINWEAPON] != nullptr;
}

#pragma endregion





