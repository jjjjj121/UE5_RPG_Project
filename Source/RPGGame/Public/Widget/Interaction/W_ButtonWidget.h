// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "W_ButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_ButtonWidget : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* PB_ButtonGauge;

public:
	void SetGauge(float Value);
};
