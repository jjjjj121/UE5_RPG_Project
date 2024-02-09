// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMenu/Inventory/Fragments/ItemFragment_Consume.h"

#include "Library/RPGFunctionLibrary.h"

#include "RPGGame/RPGGamePlayerState.h"

bool UItemFragment_Consume::OnUseItem(UItemInstance* _Instance) const
{
	UE_LOG(LogTemp, Warning, TEXT("[UItemFragment_Consume] : OnUseItem"));

	return false;
}
