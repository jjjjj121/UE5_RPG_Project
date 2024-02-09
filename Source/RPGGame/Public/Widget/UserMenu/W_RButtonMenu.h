// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "Library/WidgetEnumLibrary.h"
#include "Library/WidgetStructLibrary.h"
#include "W_RButtonMenu.generated.h"

class UItemDefinition;

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_RButtonMenu : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UVerticalBox* VB_Menu;

	class UW_InventorySlot* TargetSlot;


public:
	UFUNCTION()
	void ShowButtonMenu(FWidgetParam WidgetParam);

	UFUNCTION()
	void HideButtonMenu(FWidgetParam WidgetParam);
public:

	void InitChild();
	void AddSlot(EButtonMenuType NewType);
};
