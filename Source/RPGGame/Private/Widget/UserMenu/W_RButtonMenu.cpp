// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/W_RButtonMenu.h"
#include "Widget/UserMenu/W_RButtonMenuSlot.h"

#include "Components/VerticalBox.h"

#include "System/RPGGameInstance.h"

#include "Kismet/GameplayStatics.h"

#include "Library/RPGWidgetFunctionLibrary.h"
#include "Library/WidgetEnumLibrary.h"

#include "Widget/UserMenu/Inventory/W_InventorySlot.h"

#include "UserMenu/Inventory/ItemDefinition.h"
#include "UserMenu/Inventory/Fragments/ItemFragment_Consume.h"
#include "UserMenu/Inventory/Fragments/ItemFragment_Equipment.h"

void UW_RButtonMenu::ShowButtonMenu(FWidgetParam WidgetParam)
{
	TargetSlot = Cast<UW_InventorySlot>(WidgetParam.WidgetParam);
	UItemDefinition* ItemDef = Cast<UItemDefinition>(WidgetParam.ObjectParam);

	InitChild();

	if (ItemDef->FindFragmentByClass(UItemFragment_Equipment::StaticClass())) {
		AddSlot(EButtonMenuType::Equip);
	}
	if (ItemDef->FindFragmentByClass(UItemFragment_Consume::StaticClass())) {
		AddSlot(EButtonMenuType::Use);
	}
	AddSlot(EButtonMenuType::ThrowAway);

	SetMousePosition();
}

void UW_RButtonMenu::HideButtonMenu(FWidgetParam WidgetParam)
{
	URPGWidgetFunctionLibrary::PopWidget(GetWorld(), EWidgetNames::RButtonMenu, EWidgetLayoutType::Option);
}

void UW_RButtonMenu::InitChild()
{
	VB_Menu->ClearChildren();
}

void UW_RButtonMenu::AddSlot(EButtonMenuType NewType)
{
	TSubclassOf<UUserWidget> WidgetClass = DATATABLE_MANAGER(GetWorld())->GetWidgetClassWithName(EWidgetNames::RButtonMenuSlot);
	if (WidgetClass) {
		UW_RButtonMenuSlot* NewSlot = CreateWidget<UW_RButtonMenuSlot>(this, WidgetClass);
		NewSlot->ParentWidget = this;
		NewSlot->SetAction(NewType);

		VB_Menu->AddChild(NewSlot);
	}

}
