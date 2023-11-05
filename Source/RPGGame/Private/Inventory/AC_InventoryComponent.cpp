// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/AC_InventoryComponent.h"
#include "RPGGame/Public/Widget/W_Inventory.h"
#include "Library/RPGWidgetFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UAC_InventoryComponent::UAC_InventoryComponent()
{

}


void UAC_InventoryComponent::ShowInventory()
{


	if (UW_Inventory* InventoryWidget = Cast<UW_Inventory>(URPGWidgetFunctionLibrary::PushWidget(GetWorld(), EWidgetNames::Inventory, EWidgetLayoutType::Option))) {
		UE_LOG(LogTemp, Warning, TEXT("INVENTORY"));

	}


	//if (InventoryWidget) {
	//	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//	if (PlayerController) {
	//		if (InventoryWidget->IsVisible()) {
	//			UE_LOG(LogTemp, Warning, TEXT("INVENTORY OFF"));
	//			InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	//			PlayerController->SetInputMode(FInputModeGameOnly());
	//			PlayerController->SetShowMouseCursor(false);
	//			UGameplayStatics::SetViewportMouseCaptureMode(GetWorld(), EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
	//		}
	//		else {
	//			UE_LOG(LogTemp, Warning, TEXT("INVENTORY ON"));
	//			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	//			PlayerController->SetInputMode(FInputModeGameAndUI());
	//			PlayerController->SetShowMouseCursor(true);
	//			UGameplayStatics::SetViewportMouseCaptureMode(GetWorld(), EMouseCaptureMode::CaptureDuringRightMouseDown);
	//		}
	//	}

	//}
}

void UAC_InventoryComponent::HideInventory()
{
	//if (UW_Inventory* InventoryWidget = Cast<UW_Inventory>(URPGWidgetFunctionLibrary::GetWidgetWithLayoutType(GetWorld(), EWidgetLayoutType::Option, EWidgetNames::Inventory))) {
	//	
	//}

	URPGWidgetFunctionLibrary::PopWidget(GetWorld(), EWidgetNames::Inventory, EWidgetLayoutType::Option);
}

bool UAC_InventoryComponent::AddItemToInventory(UItemDefinition* NewItemDef){

	if (NewItemDef) {
		
		TArray<UItemInstance*>* NewItemList = nullptr;

		NewItemList = &ItemLists[NewItemDef->Category].List;

		if (NewItemList->Num() >= ItemLists[NewItemDef->Category].MaxListValue) { return false; }

		if (NewItemList) {
			if (NewItemDef->IsStack) {
				for (UItemInstance* Item : *NewItemList) {
					//�κ��丮�� �ִ� �������� ���
					if (Item->ItemDefinition->ItemID == NewItemDef->ItemID) {
						++Item->ItemStack;
						return true;
					}
				}
			}

			//�� �� �������� ���� �߰��ϴ� ���
			/*Item ȹ�� Pop up ����(�ؾ���)*/
			UItemInstance* NowItem = NewObject<UItemInstance>(this);

			if (NowItem) {
				NowItem->ItemDefinition = NewItemDef;
				NowItem->ItemStack = 1;
				NewItemList->Add(NowItem);
				return true;
			}
		}
	}

	return false;
}

