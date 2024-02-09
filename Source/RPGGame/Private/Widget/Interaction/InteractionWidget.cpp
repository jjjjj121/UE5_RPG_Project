// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Interaction/InteractionWidget.h"
#include "Widget/Interaction/InteractionItemWidget.h"
#include "Widget/Interaction/W_RootItem.h"
#include "Widget/Interaction/W_KeyTutorial.h"

#include "Library/WidgetStructLibrary.h"
#include "Library/RPGWidgetFunctionLibrary.h"

#include "RPGGame/RPGGameCharacter.h"

#include "Interface/InteractionComponent.h"
#include "Interface/InteractionInterface.h"

#include "Monster/Monster_AI.h"

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BP_W_InteractionItem->KeyTutorial = BP_W_KeyTutorial;
	BP_W_InteractionItem->ParentWidget = this;
	BP_W_KeyTutorial->ParentWidget = this;

}

void UInteractionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	switch (InteractType)
	{
	case EInteractionType::None:
		BP_W_InteractionItem->SetVisibility(ESlateVisibility::Hidden);
		BP_W_KeyTutorial->SetVisibility(ESlateVisibility::Visible);
		if (BP_W_RootItem->IsVisible()) {
			BP_W_KeyTutorial->StopAllAnimations();
			BP_W_KeyTutorial->SetRenderOpacity(0.f);
		}
		BP_W_RootItem->SetVisibility(ESlateVisibility::Hidden);
		break;
		/*Interact 감지*/
	case EInteractionType::InteractItem:
		BP_W_InteractionItem->SetVisibility(ESlateVisibility::Visible);
		BP_W_KeyTutorial->SetVisibility(ESlateVisibility::Visible);
		BP_W_RootItem->SetVisibility(ESlateVisibility::Hidden);
		break;
		/*Root Item List Open*/
	case EInteractionType::RootItem:
		BP_W_InteractionItem->SetVisibility(ESlateVisibility::Hidden);
		BP_W_KeyTutorial->SetVisibility(ESlateVisibility::Hidden);
		BP_W_RootItem->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

void UInteractionWidget::ExecuteInteraction(FWidgetParam WidgetParam)
{
	if(InteractType == EInteractionType::RootItem){
		InteractType = WidgetParam.BoolParam ? EInteractionType::RootItem : EInteractionType::None;
	}
	else {
		InteractType = WidgetParam.BoolParam ? EInteractionType::InteractItem : EInteractionType::None;
	}

	if (WidgetParam.BoolParam){
		/*Interaction Item Position*/
		BP_W_InteractionItem->SetInteractionItem(WidgetParam.VectorParam, WidgetParam.NameParam);

		/*RootItem List Set*/
		BP_W_RootItem->SetRootItems(IInteractionInterface::Execute_GetRootItemList(WidgetParam.ActorParam));
	}
}

void UInteractionWidget::PressInteractKey(FWidgetParam WidgetParam)
{
	/*OpenRootItems*/
	if (InteractType == EInteractionType::InteractItem) {
		InteractType = EInteractionType::RootItem;
		UE_LOG(LogTemp, Warning, TEXT("[UInteractionWidget] : Open Root items"));
	}
	else if (InteractType == EInteractionType::RootItem) {
		if (TriggerTime <= 0) {
			/*Button Hold 가 아닌 경우*/
			if (ARPGGameCharacter* Player = Cast<ARPGGameCharacter>(WidgetParam.ActorParam)) {
				UItemInstance* NewInstance = BP_W_RootItem->GetSelectItemInstance();
				if (Player->GetinteractionComponent()->ExecuteInteraction(NewInstance)) {
					UE_LOG(LogTemp, Warning, TEXT("GET ITEM "));
					BP_W_RootItem->GetItem();

				}
			}
		}
		else {
			/*Button Hold 중 : Trigger 도중 취소 및 오버*/
			TriggerTime = 0.f;
			BP_W_RootItem->SetButtonGauge(TriggerTime);
		}
	}
}

void UInteractionWidget::TriggerInteractKey(FWidgetParam WidgetParam)
{
	if (InteractType == EInteractionType::RootItem) {
		TriggerTime += WidgetParam.FloatParam * 2;
		BP_W_RootItem->SetButtonGauge(TriggerTime);

		if (TriggerTime >= 1.f) {
			InteractType = EInteractionType::InteractItem;
			if (ARPGGameCharacter* Player = Cast<ARPGGameCharacter>(WidgetParam.ActorParam)) {
				for (UItemInstance* Item : BP_W_RootItem->GetRootItems()) {
					if (Player->GetinteractionComponent()->ExecuteInteraction(Item)) {
						BP_W_RootItem->GetItem();
						UE_LOG(LogTemp, Warning, TEXT("123123123123"));
					}
				}
			}
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("TriggerTime : %f"), TriggerTime);
}

void UInteractionWidget::SelectRootList(FWidgetParam WidgetParam)
{
	BP_W_RootItem->Scroll(WidgetParam.BoolParam);
	
	if (WidgetParam.BoolParam) {
		UE_LOG(LogTemp, Warning, TEXT("LIST UP"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("LIST Down"));
	}
}
