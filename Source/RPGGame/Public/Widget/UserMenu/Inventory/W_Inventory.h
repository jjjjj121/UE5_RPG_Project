// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"

#include "RPGGame/EnumHeader.h"
#include "Library/WidgetEnumLibrary.h"

#include "UserMenu/AC_UserMenuComponent.h"
#include "W_Inventory.generated.h"

class UItemInstance;
class UUniformGridPanel;
class UButton;
class UImage;
class UTextBlock;

/**
 *
 */
UCLASS()
class RPGGAME_API UW_Inventory : public URPGUserWidgetBase
{
	GENERATED_BODY()

private:
	int32 LineSlotNum = 4;

	UPROPERTY(VisibleAnywhere)
	TMap<EItemCategoryType, UUniformGridPanel*> GridPanelList;

public:
	/*Uniform Grid Panel*/
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UUniformGridPanel* UGP_MeleeWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UUniformGridPanel* UGP_RangeWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UUniformGridPanel* UGP_Sheild;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UUniformGridPanel* UGP_Clothes;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UUniformGridPanel* UGP_Material;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UUniformGridPanel* UGP_Comsumable;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UUniformGridPanel* UGP_Special;

	/*Button*/
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UButton* BT_MeleeWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UButton* BT_RangeWeapon;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UButton* BT_Shields;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UButton* BT_Clothes;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UButton* BT_Material;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UButton* BT_Consumable;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
		UButton* BT_Special;

	/*Slect Item*/
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	UImage* IMG_ItemIcon;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	UTextBlock* TB_ItemName;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	UTextBlock* TB_ItemDescription;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> SlotWidgetclass;

	/*Default*/
	UPROPERTY(EditAnywhere, Category = "Defualt")
	UTexture2D* DefaultIcon;

public:
	class UW_MenuLayout* ParentWidget;

	//TMap<int32, class UW_InventorySlot*> InventorySlotList;


public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
		void OnClicked_MeleeWeapon();

	UFUNCTION()
		void OnClicked_RangeWeapon();

	UFUNCTION()
		void OnClicked_Shields();

	UFUNCTION()
		void OnClicked_Clothes();

	UFUNCTION()
		void OnClicked_Material();

	UFUNCTION()
		void OnClicked_Consumable();

	UFUNCTION()
		void OnClicked_Special();

public:
	void UpdateAllList(TMap<EItemCategoryType, FItemInstanceArray> _Inventory, TMap<EItemCategoryType, int32> _ListMaxNum);
	void UpdateList(TArray<UItemInstance*> ItemList, UUniformGridPanel* TargetGrid, int32 MaxList);

	void ShowGrid(EItemCategoryType ShowGrid);

	void UpdateSelectItem(UItemInstance* NewItemInstance);

	bool RemoveItem(UItemInstance* NewItemInstance, int32 Num);
};
