// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/W_RButtonMenuSlot.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/Character.h"

#include "Library/RPGFunctionLibrary.h"
#include "Library/RPGWidgetFunctionLibrary.h"
#include "Library/WidgetEnumLibrary.h"

#include "Widget/UserMenu/W_RButtonMenu.h"
#include "Widget/UserMenu/Inventory/W_InventorySlot.h"
#include "Widget/UserMenu/W_MenuLayout.h"
#include "Widget/UserMenu/W_Quantity.h"

#include "System/RPGGameInstance.h"

#include "UserMenu/Inventory/ItemActor.h"
#include "UserMenu/Inventory/ItemDefinition.h"

void UW_RButtonMenuSlot::NativeConstruct()
{
	Super::NativeConstruct();

	BT_Slot->OnClicked.AddDynamic(this, &UW_RButtonMenuSlot::OnClicked_Button);
}

void UW_RButtonMenuSlot::SetAction(EButtonMenuType NewType)
{
	ActionType = NewType;

	switch (ActionType)
	{
	case EButtonMenuType::Equip:
		TB_Action->SetText(FText::FromString(TEXT("장착")));
		break;
	case EButtonMenuType::NonEquip:
		TB_Action->SetText(FText::FromString(TEXT("장착 해제")));
		break;
	case EButtonMenuType::Use:
		TB_Action->SetText(FText::FromString(TEXT("사용")));
		break;
	case EButtonMenuType::ThrowAway:
		TB_Action->SetText(FText::FromString(TEXT("버리다")));
		break;
	case EButtonMenuType::ETC:
		break;
	default:
		break;
	}
}

void UW_RButtonMenuSlot::OnClicked_Button()
{
	//UE_LOG(LogTemp, Warning, TEXT("[UW_RButtonMenuSlot] : OnClicked_Button"));

	switch (ActionType)
	{
	case EButtonMenuType::Equip:
		UE_LOG(LogTemp, Warning, TEXT("[UW_RButtonMenuSlot] : Equip"));
		ParentWidget->TargetSlot->EquipItem();
		break;
	case EButtonMenuType::NonEquip:
		UE_LOG(LogTemp, Warning, TEXT("[UW_RButtonMenuSlot] : NonEquip"));
		break;
	case EButtonMenuType::Use:
		UE_LOG(LogTemp, Warning, TEXT("[UW_RButtonMenuSlot] : Use"));
		ParentWidget->TargetSlot->UseItem();
		break;
	case EButtonMenuType::ThrowAway:
	{
		FItemData ItemData = ParentWidget->TargetSlot->ItemInstance->ItemDefinition->GetItemData();

		if (ItemData.IsStack) {

			TSubclassOf<UUserWidget> WidgetClass = DATATABLE_MANAGER(GetWorld())->GetWidgetClassWithName(EWidgetNames::Quantity);
			if (WidgetClass) {

				UW_Quantity* QuantityWidget = Cast<UW_Quantity>(URPGWidgetFunctionLibrary::PushWidget(GetWorld(), EWidgetNames::Quantity, EWidgetLayoutType::Option, EWidgetAnchorType::None));

				QuantityWidget->TargetSlot = ParentWidget->TargetSlot;
				QuantityWidget->SetMousePosition();

			}
		}
		else {
			ParentWidget->TargetSlot->ThrowAwayItem();
		}
	}

	break;
	case EButtonMenuType::ETC:
		break;
	default:
		break;
	}


	FWidgetParam WidgetParam;
	ParentWidget->HideButtonMenu(WidgetParam);

}
