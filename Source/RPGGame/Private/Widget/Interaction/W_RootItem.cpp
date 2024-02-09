// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Interaction/W_RootItem.h"
#include "Widget/Interaction/W_RootItemSlot.h"
#include "Components/ScrollBox.h"

#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"

#include "Widget/Interaction/W_ButtonWidget.h"

#include "RPGGame/RPGGamePlayerController.h"

void UW_RootItem::NativeConstruct()
{
	OnVisibilityChanged.AddDynamic(this, &UW_RootItem::OnVisibility);
}

void UW_RootItem::OnVisibility(ESlateVisibility InVisibility)
{
	//InVisibility == ESlateVisibility::Visible ? ActiveList() : DeactivateList();

	ARPGGamePlayerController* Owner = Cast<ARPGGamePlayerController>(GetOwningPlayer());

	if (InVisibility == ESlateVisibility::Visible) {
		Owner->SetWheelType(EWheelType::ListType);
		ActiveList();
	}
	else if(InVisibility == ESlateVisibility::Hidden){
		Owner->SetWheelType(EWheelType::Default);
		DeactivateList();
	}


}

void UW_RootItem::ActiveList()
{
	if (SlotWidgetclass && RootItems.Num()) {
		//UE_LOG(LogTemp, Warning, TEXT("[UW_RootItem] ActiveList"));
		for (UItemInstance* Item : RootItems) {
			if (UW_RootItemSlot* RootItemSlot = Cast<UW_RootItemSlot>(CreateWidget(GetWorld(), SlotWidgetclass))) {
				UE_LOG(LogTemp, Warning, TEXT("[UW_RootItem] : ActiveList"));
				SB_RootItemList->AddChild(RootItemSlot);
				FMargin NewPadding;
				//NewPadding.Left = 10.f;
				NewPadding.Top = 5.f;
				RootItemSlot->SetPadding(NewPadding);
				RootItemSlot->SetItemData(Item);
			}
		}

		/*Init*/
		CurSlotIndex = 0;
		CurOffsetIndex = 0;
		SelectSlot(CurSlotIndex);
	}


}

void UW_RootItem::DeactivateList()
{
	SB_RootItemList->ClearChildren();
}

void UW_RootItem::Scroll(bool IsSelectUp)
{
	DeselectSlot(CurSlotIndex);

	/*True : Up / False : Down*/
	CurSlotIndex = FMath::Clamp<int32>(IsSelectUp ? --CurSlotIndex : ++CurSlotIndex, 0, SB_RootItemList->GetChildrenCount()-1);
	SelectSlot(CurSlotIndex);
	SetScrollOffset(IsSelectUp);
}

void UW_RootItem::SelectSlot(int32 SlotIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("SLECT SLOT INDEX : %d"), SlotIndex);
	if (UW_RootItemSlot* SelectSolt = Cast<UW_RootItemSlot>(SB_RootItemList->GetChildAt(SlotIndex))) {
		SelectSolt->SetSelect(true);
	}
}

void UW_RootItem::DeselectSlot(int32 SlotIndex)
{
	if (UW_RootItemSlot* DeSelectSolt = Cast<UW_RootItemSlot>(SB_RootItemList->GetChildAt(SlotIndex))) {
		DeSelectSolt->SetSelect(false);
	}
}

void UW_RootItem::SetScrollOffset(bool IsSelectUp)
{
	IsSelectUp ? CurOffsetIndex-- : CurOffsetIndex++;

	float NewOffset = 0.f;
	float ScrollValue = SB_RootItemList->GetScrollOffsetOfEnd() / (SB_RootItemList->GetChildrenCount() - 4);
	float EndOffset = SB_RootItemList->GetScrollOffsetOfEnd();

	if (CurOffsetIndex < 0) {
		NewOffset = FMath::Clamp<float>(SB_RootItemList->GetScrollOffset()- ScrollValue, 0.f, EndOffset);
		CurOffsetIndex = 0;
		SB_RootItemList->SetScrollOffset(NewOffset);
	}
	else if (CurOffsetIndex > 3) {
		NewOffset = FMath::Clamp<float>(SB_RootItemList->GetScrollOffset() + ScrollValue, 0.f, EndOffset);
		CurOffsetIndex = 3;
		SB_RootItemList->SetScrollOffset(NewOffset);
	}


}

void UW_RootItem::SetButtonGauge(float GaugeValue)
{
	BP_W_ButtonWidget->SetGauge(GaugeValue);
}

void UW_RootItem::GetItem()
{
	
	int32 EndIndex = SB_RootItemList->GetChildrenCount() - 1;
	SB_RootItemList->RemoveChildAt(CurSlotIndex);
	RootItems.RemoveAt(CurSlotIndex);

	CurSlotIndex == EndIndex ? CurSlotIndex = FMath::Clamp<int32>(--CurSlotIndex, 0 , EndIndex) : CurSlotIndex;


	SelectSlot(CurSlotIndex);

}

UItemInstance* UW_RootItem::GetSelectItemInstance()
{
	if (UW_RootItemSlot* CurSlot = Cast<UW_RootItemSlot>(SB_RootItemList->GetChildAt(CurSlotIndex))) {
		return CurSlot->ItemInstance;
	}

	return nullptr;

}
