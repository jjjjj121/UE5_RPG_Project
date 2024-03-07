// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/Inventory/W_InventorySlot.h"

#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"
#include "UserMenu/Inventory/ItemActor.h"
#include "UserMenu/Inventory/Fragments/ItemFragment_Consume.h"
#include "UserMenu/Inventory/Fragments/ItemFragment_Equipment.h"

#include "UserMenu/AC_UserMenuComponent.h"

#include "RPGGame/RPGGamePlayerController.h"

#include "Widget/UserMenu/Inventory/W_Inventory.h"
#include "Widget/UserMenu/W_MenuLayout.h"

#include "Kismet/GameplayStatics.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Border.h"

#include "System/RPGGameInstance.h"
#include "Library/RPGFunctionLibrary.h"
#include "Library/RPGWidgetFunctionLibrary.h"

#include "Input/Reply.h"

void UW_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	BT_ItemButton->OnClicked.AddDynamic(this, &UW_InventorySlot::OnClicked_Item);

	Update(ItemInstance);
}

void UW_InventorySlot::Update(UItemInstance* NewItem)
{
	ItemInstance = NewItem;

	if (ItemInstance) {
		//UItemDefinition* ItemDef = Cast<UItemDefinition>(ItemInstance->ItemDefinition.GetDefaultObject());
		FItemData ItemData = ItemInstance->ItemDefinition->GetItemData();

		IMG_Item->SetBrushFromTexture(ItemData.ItemIcon);
		IMG_Item->SetVisibility(ESlateVisibility::HitTestInvisible);
		SetItemGrade(ItemData.ItemGrade);

		if (ItemData.IsStack) {
			TB_Stack->SetText(FText::FromString(FString::FromInt(ItemInstance->ItemStack)));
		}
		else {
			TB_Stack->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else {
		IMG_Item->SetVisibility(ESlateVisibility::Collapsed);
		TB_Stack->SetVisibility(ESlateVisibility::Collapsed);
		SetItemGrade(EItemGrade::None);
	}
}

void UW_InventorySlot::SetItemGrade(EItemGrade Grade)
{
	/*Set Grade*/
	FLinearColor GradeColor;
	switch (Grade)
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
		GradeColor = EItemGradeColor::None;
	}
	B_ItemGrade->SetBrushColor(GradeColor);
}


void UW_InventorySlot::ThrowAwayItem(int32 Num)
{
	/*Inventory Compnent Item Remove*/
	FString SpawnItemID = ItemInstance->ItemID;

	if (RemoveItem(Num)) {
		AItemActor* NewItem = URPGFunctionLibrary::SpawnItemtoPlayer(GetWorld(), SpawnItemID);
		NewItem->ItemInstance->ItemStack = Num;
	}

}

bool UW_InventorySlot::RemoveItem(int32 Num)
{
	if (ParentWidget->RemoveItem(ItemInstance, Num)) {

		return true;
	}

	return false;

}

void UW_InventorySlot::UseItem()
{
	if (ItemInstance) {
		for (UItemFragment* Fragment : ItemInstance->ItemDefinition->Fragments) {
			if (Fragment->IsA(UItemFragment_Consume::StaticClass())) {
				Fragment->OnUseItem(ItemInstance);
				RemoveItem();
			}
		}
	}
}

void UW_InventorySlot::EquipItem()
{
	if (ItemInstance) {
		for (UItemFragment* Fragment : ItemInstance->ItemDefinition->Fragments) {
			if (Fragment->IsA(UItemFragment_Equipment::StaticClass())) {
				Fragment->OnUseItem(ItemInstance);
				RemoveItem();
			}
		}
	}
}

void UW_InventorySlot::OnClicked_Item()
{
	if (ParentWidget) {
		ParentWidget->UpdateSelectItem(ItemInstance);
	}

}

FReply UW_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	/*Button Option Menu*/
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true) {
		if (ItemInstance != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("RIGHT MOUSE BUTTON DOWN"));

			URPGUserWidgetBase* NewWidget = URPGWidgetFunctionLibrary::GetWidgetWithLayoutType(GetWorld(), EWidgetLayoutType::Option, EWidgetNames::RButtonMenu);

			if (NewWidget == nullptr) {
				NewWidget = URPGWidgetFunctionLibrary::PushWidget(GetWorld(), EWidgetNames::RButtonMenu, EWidgetLayoutType::Option, EWidgetAnchorType::None);
			}

			FWidgetParam WidgetParam;
			WidgetParam.ObjectParam = ItemInstance->ItemDefinition;
			WidgetParam.WidgetParam = this;
			URPGWidgetFunctionLibrary::ExecuteWidgetSingle(GetWorld(), EWidgetNames::RButtonMenu, EWidgetFunctionNames::RButtonMenu_Show, WidgetParam);

			//NewWidget->ShowButtonMenu();

		}

	}

	return Reply.NativeReply;
}
