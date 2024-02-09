// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Interaction/InteractionItemWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Components/TextBlock.h"
#include "Widget/Interaction/W_KeyTutorial.h"
#include "Widget/Interaction/InteractionWidget.h"

#include "Library/RPGWidgetFunctionLibrary.h"
#include "Library/WidgetStructLibrary.h"

void UInteractionItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnVisibilityChanged.AddDynamic(this, &UInteractionItemWidget::OnVisibility);
	//UE_LOG(LogTemp, Warning, TEXT("[UInteractionItemWidget] : NativeConstruct"));
}

void UInteractionItemWidget::SetInteractionItem(const FVector& Location, const FName& ActorName)
{
	TB_InteractActorName->SetText(FText::FromName(ActorName));

	if (APlayerController* PlayerCtrl = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FVector2D ScreenLocation = FVector2D::ZeroVector;
		PlayerCtrl->ProjectWorldLocationToScreen(Location, ScreenLocation);

		int32 ScreenSizeX = 0;
		int32 ScreenSizeY = 0;
		PlayerCtrl->GetViewportSize(ScreenSizeX, ScreenSizeY);

		const FVector2D& WidgetLocation = ScreenLocation - (FVector2D(ScreenSizeX, ScreenSizeY) * 0.5f);
		SetRenderTranslation(WidgetLocation);
	}
}

void UInteractionItemWidget::OnVisibility(ESlateVisibility InVisibility)
{
	UE_LOG(LogTemp, Warning, TEXT("[UInteractionItemWidget] : OnVisibility"));

	bool BoolParam = InVisibility == ESlateVisibility::Visible ? true : false;
	FString KeyParam = TEXT("E");				//Key
	FString DescriptionParam = TEXT("열기");		//Description

	KeyTutorial->SetTutorialText(KeyParam, DescriptionParam);

	if (!BoolParam) {
		/*Interact 범위에서 벗어날 경우*/
		if (ParentWidget->InteractType == EInteractionType::RootItem) {
			return;
		}
		else {
			ParentWidget->InteractType = EInteractionType::None;
		}
	}

	KeyTutorial->PlayShowAnim(BoolParam);


}
