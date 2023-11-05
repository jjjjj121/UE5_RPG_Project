// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "LayoutWidget.generated.h"

class UCanvasPanel;

/**
 * 
 */
UCLASS()
class RPGGAME_API ULayoutWidget : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	UCanvasPanel* GetPanel() const { return Panel; }

protected:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UCanvasPanel* Panel;



};
