// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidgetBase.h"
#include "W_HUD.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UW_HUD : public URPGUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "HUDWidget", meta = (BindWidget))
		class UImage* IMG_HP_line;

	UPROPERTY(BlueprintReadOnly, Category = "HUDWidget", meta = (BindWidget))
		class UImage* IMG_HP_tail;

	UPROPERTY(BlueprintReadOnly, Category = "HUDWidget", meta = (BindWidget))
		class UImage* IMG_MP_line;

	UPROPERTY(BlueprintReadOnly, Category = "HUDWidget", meta = (BindWidget))
		class UImage* IMG_MP_tail;

	UPROPERTY(BlueprintReadOnly, Category = "HUDWidget", meta = (BindWidget))
		class UProgressBar* PB_HPbar;

	UPROPERTY(BlueprintReadOnly, Category = "HUDWidget", meta = (BindWidget))
		class UProgressBar* PB_MPbar;

	UPROPERTY(BlueprintReadOnly, Category = "HUDWidget", meta = (BindWidget))
		class UW_CheckRoot* BP_W_CheckRoot;

	UPROPERTY(BlueprintReadOnly, Category = "HUDWidget", meta = (BindWidget))
		class UW_RootItem* BP_W_RootItem;

	UPROPERTY(BlueprintReadWrite, Category = "Value", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float W_HP_Per;

	UPROPERTY(BlueprintReadWrite, Category = "Value", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float W_MP_Per;


};
