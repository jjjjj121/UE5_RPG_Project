// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/Equipment/W_State.h"
#include "Widget/UserMenu/Equipment/W_StateData.h"

void UW_State::SetState(FRPGPlayerState NewState)
{
	Slot_Level->UpdateValue(FText::AsNumber(NewState.Level));
}
