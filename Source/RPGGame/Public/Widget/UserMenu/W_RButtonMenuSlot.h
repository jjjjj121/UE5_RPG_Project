// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "Library/WidgetEnumLibrary.h"
#include "W_RButtonMenuSlot.generated.h"

class UW_RButtonMenu;

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_RButtonMenuSlot : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BT_Slot;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TB_Action;

	EButtonMenuType ActionType;

	UW_RButtonMenu* ParentWidget;

protected:
	virtual void NativeConstruct() override;

public:
	void SetAction(EButtonMenuType NewType);

private:
	UFUNCTION()
		virtual void OnClicked_Button();
};
