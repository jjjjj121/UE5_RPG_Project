// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/UserMenu/Inventory/W_InventorySlot.h"
#include "W_EquipSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_EquipSlot : public UW_InventorySlot
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		UTexture2D* DefaultIcon;


protected:
	virtual void NativeConstruct() override;

public:
	virtual void Update(UItemInstance* NewItem) override;

public:
	virtual void OnClicked_Item() override;

	void InitDefault();

private:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
