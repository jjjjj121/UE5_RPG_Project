// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/UserMenu/Equipment/W_EquipSlot.h"

#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"

#include "RPGGame/Structs.h"

#include "Components/Image.h"
#include "Components/Border.h"

void UW_EquipSlot::NativeConstruct()
{
	//Super::NativeConstruct();

	if (DefaultIcon != nullptr) {
		InitDefault();
	}

}

void UW_EquipSlot::Update(UItemInstance* NewItem)
{
	Super::Update(NewItem);

	if (ItemInstance) {
		IMG_Item->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
	else {
		InitDefault();
	}

}

void UW_EquipSlot::OnClicked_Item()
{
	UE_LOG(LogTemp, Warning, TEXT("EQUIP SLOT : ON CLICK"));
}

void UW_EquipSlot::InitDefault()
{
	IMG_Item->SetBrushFromTexture(DefaultIcon);
	IMG_Item->SetBrushTintColor(FLinearColor(0.2f, 0.2f, 0.2f, 1.f));
	SetItemGrade(EItemGrade::None);
}

FReply UW_EquipSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;

	UE_LOG(LogTemp, Warning, TEXT("[UW_EquipSlot] :RIGHT MOUSE BUTTON DOWN"));

	//Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true) {
	//	if (ItemInstance != nullptr) {
	//		if (ParentWidget->ParentWidget->RButtonMenuWidget == nullptr) {

	//			UE_LOG(LogTemp, Warning, TEXT("RIGHT MOUSE BUTTON DOWN"));
	//			URPGUserWidgetBase* NewWidget = CreateWidget<URPGUserWidgetBase>(this, RButtonWidget);
	//			NewWidget->AddToViewport();
	//			ParentWidget->ParentWidget->SetRButtonMenuWidget(NewWidget);
	//		}

	//		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//		FVector2D ViewportPosition;
	//		Controller->GetMousePosition(ViewportPosition.X, ViewportPosition.Y);

	//		ParentWidget->ParentWidget->RButtonMenuWidget->SetPositionInViewport(ViewportPosition);
	//	}
	//}

	return Reply.NativeReply;
}
