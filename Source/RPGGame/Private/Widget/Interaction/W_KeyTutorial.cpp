// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Interaction/W_KeyTutorial.h"
#include "Widget/Interaction/InteractionWidget.h"
#include "Components/TextBlock.h"


void UW_KeyTutorial::NativeConstruct()
{
	Super::NativeConstruct();

	SetRenderOpacity(0.f);
}

void UW_KeyTutorial::SetTutorialText(FString Key, FString Description)
{
	TB_Key->SetText(FText::FromString(Key));
	TB_Description->SetText(FText::FromString(Description));

}

void UW_KeyTutorial::PlayShowAnim(bool IsForward)
{

	if (ParentWidget->InteractType != EInteractionType::RootItem) {
		if (IsForward) {
			PlayAnimationForward(ShowAnim);
		}
		else {
			PlayAnimationReverse(ShowAnim);
		}
	}
}
