// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/W_MenuLayout.h"

#include "Library/RPGWidgetFunctionLibrary.h"
#include "Library/RPGFunctionLibrary.h"

#include "RPGGame/RPGGamePlayerController.h"
#include "UserMenu/AC_UserMenuComponent.h"

#include "Widget/UserMenu/Inventory/W_Inventory.h"
#include "Widget/UserMenu/Equipment/W_Equipment.h"

#include "Components/Button.h"

#include "System/RPGGameInstance.h"

void UW_MenuLayout::NativeConstruct()
{
	bUseCursor = true;
	bOnlyUIControl = true;

	Super::NativeConstruct();

	BP_W_Inventory->ParentWidget = this;

	UserMenuWidgets.Add(EUserMenuType::Inventory, BP_W_Inventory);
	UserMenuWidgets.Add(EUserMenuType::Equipment, BP_W_Equipment);
	UserMenuWidgets.Add(EUserMenuType::Map, BP_W_Map);
	UserMenuWidgets.Add(EUserMenuType::Quest, BP_W_Quest);

	BT_Equip->OnClicked.AddDynamic(this, &UW_MenuLayout::OnClicked_Equip);
	BT_Inventory->OnClicked.AddDynamic(this, &UW_MenuLayout::OnClicked_Inventory);
	BT_Quest->OnClicked.AddDynamic(this, &UW_MenuLayout::OnClicked_Quest);
	BT_Map->OnClicked.AddDynamic(this, &UW_MenuLayout::OnClicked_Map);
}

/*On Click Button Func*/
void UW_MenuLayout::OnClicked_Equip() { ShowMenu(EUserMenuType::Equipment); }
void UW_MenuLayout::OnClicked_Inventory(){ ShowMenu(EUserMenuType::Inventory); }
void UW_MenuLayout::OnClicked_Quest(){ ShowMenu(EUserMenuType::Quest); }
void UW_MenuLayout::OnClicked_Map(){ ShowMenu(EUserMenuType::Map); }


void UW_MenuLayout::InputBindEvents()
{
	Super::InputBindEvents();

	if (InputComponent){
		InputComponent->BindKey(EKeys::I, IE_Pressed, this, &UW_MenuLayout::OnInventoryMenuKey).bExecuteWhenPaused = true;
		InputComponent->BindKey(EKeys::J, IE_Pressed, this, &UW_MenuLayout::OnEquipMenuKey).bExecuteWhenPaused = true;
		InputComponent->BindKey(EKeys::K, IE_Pressed, this, &UW_MenuLayout::OnQuestMenuKey).bExecuteWhenPaused = true;
		InputComponent->BindKey(EKeys::M, IE_Pressed, this, &UW_MenuLayout::OnMapMenuKey).bExecuteWhenPaused = true;

	}
}

FReply UW_MenuLayout::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) {
		UE_LOG(LogTemp, Warning, TEXT("[UW_MenuLayout] : MOUSE BUTTON DOWN"));

		FWidgetParam WidgetParam;
		URPGWidgetFunctionLibrary::ExecuteWidgetSingle(GetWorld(), EWidgetNames::RButtonMenu, EWidgetFunctionNames::RButtonMenu_Hide, WidgetParam);
		
	}

	return Reply.NativeReply;
}

void UW_MenuLayout::ShowMenu(EUserMenuType ShowMenu)
{
	for (auto Widget : UserMenuWidgets) {
		Widget.Key == ShowMenu ? Widget.Value->SetVisibility(ESlateVisibility::Visible) : Widget.Value->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UW_MenuLayout::InitInventory(TMap<EItemCategoryType, FItemInstanceArray> _Inventory, TMap<EItemCategoryType, int32> _ListMaxNum)
{
	BP_W_Inventory->UpdateAllList(_Inventory, _ListMaxNum);
}

void UW_MenuLayout::InitEquipInventory(TMap<EEquipCategoryType, UItemInstance*> _EquipInventory)
{
	BP_W_Equipment->UpdateAllList(_EquipInventory);
}


#pragma region Input
void UW_MenuLayout::OnInventoryMenuKey()
{
	UE_LOG(LogTemp, Warning, TEXT("[UW_MenuLayout] : OnInventoryMenuKey"));

	if (BP_W_Inventory->GetVisibility() == ESlateVisibility::Visible) {
		if (ARPGGamePlayerController* PlayerController = URPGFunctionLibrary::GetPlayerController(GetWorld())){
			if (PlayerController->UserMenuComp){
				PlayerController->UserMenuComp->HideUserMenu();
			}
		}
	}
	else {
		ShowMenu(EUserMenuType::Inventory);
	}
}

void UW_MenuLayout::OnEquipMenuKey()
{
	UE_LOG(LogTemp, Warning, TEXT("[UW_MenuLayout] : OnEquipMenuKey"));

	if (BP_W_Equipment->GetVisibility() == ESlateVisibility::Visible) {
		if (ARPGGamePlayerController* PlayerController = URPGFunctionLibrary::GetPlayerController(GetWorld())) {
			if (PlayerController->UserMenuComp) {
				PlayerController->UserMenuComp->HideUserMenu();
			}
		}
	}
	else {
		ShowMenu(EUserMenuType::Equipment);
	}
}

void UW_MenuLayout::OnQuestMenuKey()
{
	UE_LOG(LogTemp, Warning, TEXT("[UW_MenuLayout] : OnQuestMenuKey"));

	if (BP_W_Quest->GetVisibility() == ESlateVisibility::Visible) {
		if (ARPGGamePlayerController* PlayerController = URPGFunctionLibrary::GetPlayerController(GetWorld())) {
			if (PlayerController->UserMenuComp) {
				PlayerController->UserMenuComp->HideUserMenu();
			}
		}
	}
	else {
		ShowMenu(EUserMenuType::Quest);
	}
}

void UW_MenuLayout::OnMapMenuKey()
{
	UE_LOG(LogTemp, Warning, TEXT("[UW_MenuLayout] : OnMapMenuKey"));

	if (BP_W_Equipment->GetVisibility() == ESlateVisibility::Visible) {
		if (ARPGGamePlayerController* PlayerController = URPGFunctionLibrary::GetPlayerController(GetWorld())) {
			if (PlayerController->UserMenuComp) {
				PlayerController->UserMenuComp->HideUserMenu();
			}
		}
	}
	else {
		ShowMenu(EUserMenuType::Map);
	}
}

void UW_MenuLayout::OnDefaultKeyTab()
{
	UE_LOG(LogTemp, Warning, TEXT("[UW_MenuLayout] : Override"));
}

#pragma endregion