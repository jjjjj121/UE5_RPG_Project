// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "RPGGame/Structs.h"
#include "W_RootItem.generated.h"

class UItemInstance;
/**
 * 
 */
UCLASS()
class RPGGAME_API UW_RootItem : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnVisibility(ESlateVisibility InVisibility);

public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
		class UScrollBox* SB_RootItemList;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
		class UW_ButtonWidget* BP_W_ButtonWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> SlotWidgetclass;

private:
	TArray<UItemInstance*> RootItems;

	int32 CurSlotIndex = 0;
	int32 CurOffsetIndex = 0;

public:
	void SetRootItems(TArray<UItemInstance*> _RootItems) { RootItems = _RootItems;}
	TArray<UItemInstance*> GetRootItems() { return RootItems; }

public:
	void ActiveList();
	void DeactivateList();

	void Scroll(bool IsSelectUp);
	void SelectSlot(int32 SlotIndex);
	void DeselectSlot(int32 SlotIndex);

	void SetScrollOffset(bool IsSelectUp);
	void SetButtonGauge(float GaugeValue);

	void GetItem();

	UItemInstance* GetSelectItemInstance();
};
