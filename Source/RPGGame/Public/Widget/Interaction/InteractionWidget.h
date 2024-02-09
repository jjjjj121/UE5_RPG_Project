// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "Library/WidgetStructLibrary.h"
#include "InteractionWidget.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	None,
	InteractItem,
	RootItem,
};


/**
 * 
 */
UCLASS()
class RPGGAME_API UInteractionWidget : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UFUNCTION()
	void ExecuteInteraction(FWidgetParam WidgetParam);

	UFUNCTION()
	void PressInteractKey(FWidgetParam WidgetParam);

	UFUNCTION()
	void TriggerInteractKey(FWidgetParam WidgetParam);

	UFUNCTION()
	void SelectRootList(FWidgetParam WidgetParam);

protected:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		class UInteractionItemWidget* BP_W_InteractionItem;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		class UW_RootItem* BP_W_RootItem;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		class UW_KeyTutorial* BP_W_KeyTutorial;

public:
	bool bRunningRoot = false;

	float TriggerTime = 0.f;

public:
	EInteractionType InteractType = EInteractionType::None;
};
