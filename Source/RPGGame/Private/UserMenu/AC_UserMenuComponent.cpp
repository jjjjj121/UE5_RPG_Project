// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMenu/AC_UserMenuComponent.h"
#include "Widget/UserMenu/W_MenuLayout.h"

#include "Library/RPGFunctionLibrary.h"
#include "Library/RPGWidgetFunctionLibrary.h"

#include "UserMenu/Inventory/ItemActor.h"
#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"

#include "Equipment/EquipmentDefinition.h"
#include "Equipment/EquipmentInstance.h"
#include "Equipment/EquipmentActor.h"
#include "Equipment/Instance/WeaponInstance.h"
#include "Equipment/Instance/ShieldInstance.h"

#include "System/RPGGameInstance.h"

#include "RPGGame/RPGGameCharacter.h"

#include "Kismet/GameplayStatics.h"


FEquipmentList::FEquipmentList()
{
	OwnerComponent = nullptr;
	InitEntries();
}

FEquipmentList::FEquipmentList(UActorComponent* OwnerComponent_)
{
	OwnerComponent = OwnerComponent_;
	InitEntries();
}

void FEquipmentList::InitEntries()
{
	//Equip Entries 초기화
	for (int i = 0; i <= static_cast<int>(EEquipCategoryType::NONE); i++) {
		Entries.Add(static_cast<EEquipCategoryType>(i), FEquipmentEntry());
	}
}

FEquipmentEntry FEquipmentList::SetNewEntry(TSubclassOf<UEquipmentDefinition> NewDefinition, FString ID)
{
	if (NewDefinition == nullptr) {
		return FEquipmentEntry();
	}

	UEquipmentInstance* EquipmentInstance = nullptr;
	const UEquipmentDefinition* EquipmentCDO = GetDefault<UEquipmentDefinition>(NewDefinition);

	if (EquipmentCDO->InstanceType == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("[FEquipmentList ^ SetNewEntry] :  Instance Type is nullptr. Check Data Table."))
			return FEquipmentEntry();
	}

	EquipmentInstance = NewObject<UEquipmentInstance>(OwnerComponent->GetOwner(), EquipmentCDO->InstanceType);
	EquipmentInstance->ItemID = ID;

	FEquipmentEntry result;
	result.Instance = EquipmentInstance;
	result.EquipmentDefinition = NewDefinition;

	return result;
}

UEquipmentInstance* FEquipmentList::AddEntry(EEquipCategoryType EquipSlotCategory, FEquipmentEntry NewEntry)
{
	if (NewEntry.Instance == nullptr) {
		return nullptr;
	}

	if (EquipSlotCategory == EEquipCategoryType::NONE) {
		return nullptr;
	}

	Entries[EquipSlotCategory] = NewEntry;
	const UEquipmentDefinition* equipmentCDO = GetDefault<UEquipmentDefinition>(Entries[EquipSlotCategory].EquipmentDefinition);

	/*Spawn Equipment Actor*/
	Entries[EquipSlotCategory].Instance->SpawnEquipmentActor(equipmentCDO->ActorToSpawn);

	return Entries[EquipSlotCategory].Instance;
}

bool FEquipmentList::RemoveEntry(EEquipCategoryType EquipSlotCategory)
{
	FEquipmentEntry& Entry = Entries[EquipSlotCategory];

	Entry.Instance->DestroyEquipmentActor();

	Entry.EquipmentDefinition = nullptr;
	Entry.Instance = nullptr;

	return true;
}

EEquipCategoryType FEquipmentList::CheckCategory(FEquipmentEntry NewEntry)
{
	if (NewEntry.Instance == nullptr) {
		return EEquipCategoryType::NONE;
	}

	EEquipmentType EquipType = NewEntry.Instance->GetEquipmentType();
	EEquipCategoryType result = EEquipCategoryType::NONE;

	switch (EquipType)
	{
	case EEquipmentType::WEAPON:
		UE_LOG(LogTemp, Warning, TEXT("Equip Category Is WEAPON"));
		result = EEquipCategoryType::MAINWEAPON;
		break;
	case EEquipmentType::SHIELD:
		UE_LOG(LogTemp, Warning, TEXT("Equip Category Is SHIELD"));
		result = EEquipCategoryType::SUBWEAPON;
		break;
	case EEquipmentType::ARROW:
		result = EEquipCategoryType::ARROW;
		break;
	case EEquipmentType::HEAD:
		result = EEquipCategoryType::HEAD;
		break;
	case EEquipmentType::TOP:
		result = EEquipCategoryType::TOP;
		break;
	case EEquipmentType::PANTS:
		result = EEquipCategoryType::PANTS;
		break;
	case EEquipmentType::GLOVES:
		result = EEquipCategoryType::GLOVES;
		break;
	case EEquipmentType::SHOES:
		result = EEquipCategoryType::SHOES;
		break;
	case EEquipmentType::SUBITEMS:
		result = EEquipCategoryType::SUBITEMS1;
		break;
	case EEquipmentType::MAX:
		break;
	default:
		break;
	}



	return result;
}


//-------------------------------------------------------------------------------------------------------------------------------
//UserMenu Componet

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

	EquipmentInventory = FEquipmentList(this);

}


void UAC_UserMenuComponent::ShowUserMenu(EUserMenuType MenuType)
{
	if (UW_MenuLayout* UserMenuWidget = Cast<UW_MenuLayout>(URPGWidgetFunctionLibrary::PushWidget(GetWorld(), EWidgetNames::Menu, EWidgetLayoutType::Option, EWidgetAnchorType::Fill))) {
		UserMenuWidget->InitInventory(Inventory, ListMaxNum);
		UserMenuWidget->InitEquipInventory(EquipmentInventory);
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

void UAC_UserMenuComponent::RefreshInventories()
{
	if (UW_MenuLayout* UserMenuWidget = Cast<UW_MenuLayout>(URPGWidgetFunctionLibrary::GetWidgetWithLayoutType(GetWorld(), EWidgetLayoutType::Option, EWidgetNames::Menu))) {
		UserMenuWidget->InitInventory(Inventory, ListMaxNum);
		UserMenuWidget->InitEquipInventory(EquipmentInventory);
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
		ItemList->InstanceList.Add(NewItemInstance);

		/*UI Update*/
		RefreshInventories();

		/*Item 획득 Pop up 실행(해야함)*/

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

					/*UI Update*/
					RefreshInventories();

					return true;
				}
			}
		}
	}


	return false;
}

#pragma endregion

#pragma region Equipment

UEquipmentInstance* UAC_UserMenuComponent::EquipItem(TSubclassOf<UEquipmentDefinition> EquipmentClass, FString ID)
{

	if (EquipmentClass == nullptr) {
		return nullptr;
	}


	UEquipmentInstance* equipmentInstance = nullptr;

	/*새로 등록할 Entry 가져오기 (등록 x)*/
	FEquipmentEntry NewEntry = EquipmentInventory.SetNewEntry(EquipmentClass, ID);
	/*Equip Slot Category 계산 후 가져오기*/
	EEquipCategoryType Category = EquipmentInventory.CheckCategory(NewEntry);
	/*가져온 정보를 토대로 EquipInventory에 최종 등록하기*/
	equipmentInstance = EquipmentInventory.AddEntry(Category, NewEntry);


	return equipmentInstance;

}

bool UAC_UserMenuComponent::UnEquipItem(EEquipCategoryType Category)
{
	TMap<EEquipCategoryType, FEquipmentEntry> entries = EquipmentInventory.GetEntries();

	if (UEquipmentInstance* PrevEquipInstance = entries[Category].Instance) {
		if (EquipmentInventory.RemoveEntry(Category)) {
			FItemTable* NewData = DATATABLE_MANAGER(GetWorld())->GetItemData(PrevEquipInstance->ItemID);
			UItemInstance* NewIns = NewObject<UItemInstance>(this);
			NewIns->InitInstance(PrevEquipInstance->ItemID);

			AddItemToInventory(NewIns);

			return true;
		}
	}

	return false;
}



bool UAC_UserMenuComponent::IsEquipWeapon()
{
	return 	EquipmentInventory.Entries[EEquipCategoryType::MAINWEAPON].GetInstance() != nullptr;
}

bool UAC_UserMenuComponent::IsEquipShield()
{
	if (UShieldInstance* SubWeaponInstance = Cast<UShieldInstance>(EquipmentInventory.Entries[EEquipCategoryType::SUBWEAPON].GetInstance())) {
		return true;
	}

	return false;
}

#pragma endregion

