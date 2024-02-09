// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"

#include "Library/WidgetEnumLibrary.h"
#include "RPGGame/EnumHeader.h"

#include "W_MenuLayout.generated.h"

class UButton;
class UW_Inventory;
class UW_Equipment;
class UItemInstance;

struct FItemInstanceArray;

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_MenuLayout : public URPGUserWidgetBase
{
	GENERATED_BODY()

public:
	/*Widget*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UW_Inventory* BP_W_Inventory;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UW_Equipment* BP_W_Equipment;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		URPGUserWidgetBase* BP_W_Map;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		URPGUserWidgetBase* BP_W_Quest;

	/*Button*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BT_Equip;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BT_Inventory;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BT_Quest;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* BT_Map;


private:
	virtual void NativeConstruct() override;
	virtual void InputBindEvents() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	void ShowMenu(EUserMenuType ShowMenu);
	void InitInventory(TMap<EItemCategoryType, FItemInstanceArray> _Inventory, TMap<EItemCategoryType, int32> _ListMaxNum);
	void InitEquipInventory(TMap<EEquipCategoryType, UItemInstance*> _EquipInventory);

private:
	TMap<EUserMenuType, URPGUserWidgetBase*> UserMenuWidgets;

private:
	UFUNCTION()
	void OnClicked_Equip();

	UFUNCTION()
	void OnClicked_Inventory();

	UFUNCTION()
	void OnClicked_Quest();

	UFUNCTION()
	void OnClicked_Map();

#pragma region Input
protected:
	virtual void OnInventoryMenuKey();
	virtual void OnEquipMenuKey();
	virtual void OnQuestMenuKey();
	virtual void OnMapMenuKey();
	virtual void OnDefaultKeyTab() override;
#pragma endregion
};
