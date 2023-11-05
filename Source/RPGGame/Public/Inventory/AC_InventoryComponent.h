// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGGame/Structs.h"
#include "ItemDefinition.h"
#include "RPGGame/Enumheader.h"
#include "ItemInstance.h"
#include "AC_InventoryComponent.generated.h"

USTRUCT()
struct FItemInstanceArray
{
	GENERATED_BODY()

public:
	TArray<UItemInstance*> List;

	UPROPERTY(EditAnywhere)
	int32 MaxListValue;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGGAME_API UAC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UAC_InventoryComponent();

public:
	UPROPERTY(VisibleAnywhere)
		TMap<EItemCategoryType, FItemInstanceArray> ItemLists;

protected:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> Inventoryclass;

	//class UW_Inventory* InventoryWidget;

public:
	void ShowInventory();
	void HideInventory();

	bool AddItemToInventory(UItemDefinition* NewItemDef);

		
};
