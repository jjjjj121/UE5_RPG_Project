// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/RPGUserWidgetBase.h"
#include "RPGGame/Structs.h"
#include "W_State.generated.h"

class UW_StateData;
/**
 * 
 */
UCLASS()
class RPGGAME_API UW_State : public URPGUserWidgetBase
{
	GENERATED_BODY()
	
public:
	/*ªÛ≈¬√¢*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UW_StateData* Slot_Level;

public:
	void SetState(FRPGPlayerState NewState);
};
