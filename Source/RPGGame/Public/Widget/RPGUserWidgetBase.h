// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Library/WidgetEnumLibrary.h"
#include "RPGUserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API URPGUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	EWidgetLayoutType LayoutType;

public:
	UFUNCTION(BlueprintPure, Category = "Widget")
	EWidgetLayoutType GetLayoutType() const { return LayoutType; }

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetWidgetLayout(EWidgetLayoutType NewLayoutType) { LayoutType = NewLayoutType; }
};
