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

	bool AddItemToInventory(UItemInstance* NewItemInstance);
	bool RemoveItemToInventory(UItemInstance* NewItemInstance, int32 Num);
#pragma endregion


#pragma region Equipment
public:
	UPROPERTY(VisibleAnywhere)
	TMap<EEquipCategoryType, UItemInstance*> EquipInventory;


public:
	bool EquipItem(UEquipmentDefinition* EquipDef, UItemInstance* NewEquipItem);
	bool UnEquipItem(EEquipCategoryType Category);
	bool SpawnAndAttach(UItemInstance* NewEquipItem);

	bool IsEquipWeapon();

#pragma endregion


		
};
