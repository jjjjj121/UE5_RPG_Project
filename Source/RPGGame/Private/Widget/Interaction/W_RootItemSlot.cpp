// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Interaction/W_RootItemSlot.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"

#include "Library/WidgetEnumLibrary.h"

void UW_RootItemSlot::SetItemData(UItemInstance* NewInstance)
{
	ItemInstance = NewInstance;

	//UItemDefinition* ItemDef = Cast<UItemDefinition>(NewData->ItemDefinition->GetDefaultObject());
	FItemData ItemData = NewInstance->ItemDefinition->GetItemData();

	/*Set Name*/
	TB_ItemName->SetText(FText::FromString(ItemData.ItemName));

	/*Set Stack*/
	TB_ItemNum->SetText(FText::FromString(FString::FromInt(ItemInstance->ItemStack)));



	/*Set Grade*/
	FLinearColor GradeColor;
	switch (ItemData.ItemGrade)
	{
	case EItemGrade::Common:
		GradeColor = EItemGradeColor::Common;
		break;
	case EItemGrade::Magic:
		GradeColor = EItemGradeColor::Magic;
		break;
	case EItemGrade::Rare:
		GradeColor = EItemGradeColor::Rare;
		break;
	case EItemGrade::Unique:
		GradeColor = EItemGradeColor::Unique;
		break;
	case EItemGrade::Legendary:
		GradeColor = EItemGradeColor::Legendary;
		break;
	case EItemGrade::None:
		break;
	}
	B_ItemGrade->SetBrushColor(GradeColor);
	
}

void UW_RootItemSlot::SetSelect(bool IsSelectSlot)
{
	IsSelectSlot ? B_Select->SetVisibility(ESlateVisibility::Visible) : B_Select->SetVisibility(ESlateVisibility::Hidden);
}
