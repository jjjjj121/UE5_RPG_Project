// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "Library/WidgetStructLibrary.h"
#include "W_Quantity.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_Quantity : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UEditableTextBox* ETB_Quantity;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BT_Accept;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BT_Cancel;

	class UW_InventorySlot* TargetSlot;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
		virtual void OnClicked_Accept();

	UFUNCTION()
		virtual void OnClicked_Cancel();

};
