// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "W_StateData.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class RPGGAME_API UW_StateData : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TB_Stat;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TB_Value;

	UPROPERTY(EditAnywhere)
	FText StatText;

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateValue(FText NewValue);

};
