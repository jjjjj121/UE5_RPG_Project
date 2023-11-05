// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidgetBase.h"
#include "RPGGame/Structs.h"
#include "W_RootItem.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_RootItem : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Slot", meta = (BindWidget))
		class UScrollBox* SB_RootItemList;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> SlotWidgetclass;

public:
	TArray<class AItem*> RootItems;

public:
	void ActiveList();
};
