// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Widget/W_HUD.h"
#include "Widget/W_CheckRoot.h"
#include "Widget/W_Inventory.h"
#include "Widget/W_RootItem.h"
#include "RPGGameCharacter.h"
#include "RPGGamePlayerController.h"

void ARPGGameHUD::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ARPGGameCharacter>(GetOwningPawn());
	Controller = Cast<ARPGGamePlayerController>(GetOwner());

	//HUDWidget = Cast<UW_HUD>(CreateWidget(GetWorld(), HUDWidgetclass));

	//if (HUDWidget) {
	//	HUDWidget->AddToViewport();
	//}

}

void ARPGGameHUD::CheckRoot()
{
	//if (HUDWidget && bRootItem) {
	//	if (HUDWidget->BP_W_RootItem->IsVisible()) {
	//		HUDWidget->BP_W_CheckRoot->SetVisibility(ESlateVisibility::Collapsed);
	//	}
	//	else {
	//		HUDWidget->BP_W_CheckRoot->SetVisibility(ESlateVisibility::Visible);
	//	}
	//}
	//else {
	//	HUDWidget->BP_W_CheckRoot->SetVisibility(ESlateVisibility::Collapsed);
	//	HUDWidget->BP_W_RootItem->SetVisibility(ESlateVisibility::Collapsed);
	//}
}


void ARPGGameHUD::OpenRootItemList()
{
	//HUDWidget->BP_W_RootItem->ActiveList();

	//Controller->WheelType = EWheelType::ListType;

	//HUDWidget->BP_W_CheckRoot->SetVisibility(ESlateVisibility::Collapsed);
	//HUDWidget->BP_W_RootItem->SetVisibility(ESlateVisibility::Visible);
	//SelectButton(0);
}

void ARPGGameHUD::SelectButton(int32 ListIndex)
{
}

void ARPGGameHUD::SetRootItemList(TArray<AItem*> NewRootItems)
{
	//HUDWidget->BP_W_RootItem->RootItems = NewRootItems;
}
