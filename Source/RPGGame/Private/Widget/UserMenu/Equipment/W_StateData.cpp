// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/Equipment/W_StateData.h"

#include "Components/TextBlock.h"

void UW_StateData::NativeConstruct()
{
	Super::NativeConstruct();

	if (!StatText.IsEmpty()) {
		TB_Stat->SetText(StatText);
	}
}

void UW_StateData::UpdateValue(FText NewValue)
{
	TB_Value->SetText(NewValue);
}
