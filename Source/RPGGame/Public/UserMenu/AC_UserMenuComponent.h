// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "RPGGame/Structs.h"
#include "RPGGame/Enumheader.h"
#include "Library/WidgetEnumLibrary.h"

#include "AC_UserMenuComponent.generated.h"

class UItemInstance;
class UEquipmentDefinition;
class UEquipmentInstance;

USTRUCT()
struct FItemInstanceArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<UItemInstance*> InstanceList;

	UPROPERTY(EditAnywhere)
		int32 MaxListValue;
};

USTRUCT()
struct FEquipmentEntry
{
	GENERATED_BODY()

private:
	friend FEquipmentList;
	friend UAC_UserMenuComponent;

private:
	UPROPERTY()
	TSubclassOf<UEquipmentDefinition> EquipmentDefinition;

	UPROPERTY()
	UEquipmentInstance* Instance;

public:
	FEquipmentEntry() : EquipmentDefinition(nullptr), Instance(nullptr){}

public:
	FORCEINLINE UEquipmentInstance* GetInstance() { return Instance; }
};


USTRUCT(BlueprintType)
struct FEquipmentList
{
	GENERATED_BODY()

private:
	friend UAC_UserMenuComponent;

private:
	UPROPERTY()
	UActorComponent* OwnerComponent;

	UPROPERTY()
	TMap<EEquipCategoryType, FEquipmentEntry> Entries;

public:
	FEquipmentList();
	FEquipmentList(UActorComponent* OwnerComponent_);

public:
	void InitEntries();
	FEquipmentEntry SetNewEntry(TSubclassOf<UEquipmentDefinition> NewDefinition, FString ID);
	UEquipmentInstance* AddEntry(EEquipCategoryType EquipSlotCategory, FEquipmentEntry NewEntry);
	bool RemoveEntry(EEquipCategoryType EquipSlotCategory);
	EEquipCategoryType CheckCategory(FEquipmentEntry NewEntry);

	FORCEINLINE TMap<EEquipCategoryType, FEquipmentEntry> GetEntries() { return Entries; }

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGGAME_API UAC_UserMenuComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAC_UserMenuComponent();

#pragma region Inventory

public:
	UPROPERTY(VisibleAnywhere)
		TMap<EItemCategoryType, FItemInstanceArray> Inventory;

	UPROPERTY(EditAnywhere)
		TMap<EItemCategoryType, int32> ListMaxNum;

protected:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget> Inventoryclass;

	//class UW_Inventory* InventoryWidget;

public:
	void ShowUserMenu(EUserMenuType MenuType);
	void HideUserMenu();
	void RefreshInventories();

	bool AddItemToInventory(UItemInstance* NewItemInstance);
	bool RemoveItemToInventory(UItemInstance* NewItemInstance, int32 Num);
#pragma endregion


#pragma region Equipment
public:
	UPROPERTY(VisibleAnywhere)
	FEquipmentList EquipmentInventory;

public:
	UEquipmentInstance* EquipItem(TSubclassOf<UEquipmentDefinition> EquipmentClass, FString ID);
	bool UnEquipItem(EEquipCategoryType Category);

	bool IsEquipWeapon();
	bool IsEquipShield();

#pragma endregion


		
};
