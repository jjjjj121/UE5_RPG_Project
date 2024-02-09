// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/RPGUserWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Components/CanvasPanelSlot.h"

void URPGUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (bOnlyUIControl)
	{
		InitializeInputComponent();
		InputBindEvents();
	}

	if (bUseCursor)
	{
		if (APlayerController* PlayerCtrl = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			PlayerCtrl->SetShowMouseCursor(true);
			PlayerCtrl->SetPause(true);
		}
	}
}

void URPGUserWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();

	if (bOnlyUIControl)
	{
		InputUnbindEvents();
	}

	if (bUseCursor)
	{
		if (APlayerController* PlayerCtrl = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			PlayerCtrl->SetShowMouseCursor(false);
			PlayerCtrl->SetPause(false);
		}
	}


}

void URPGUserWidgetBase::InputBindEvents()
{
	if (InputComponent)
	{
		InputComponent->BindKey(EKeys::Up, IE_Pressed, this, &URPGUserWidgetBase::OnDefaultKeyUp).bExecuteWhenPaused = true;
		InputComponent->BindKey(EKeys::Down, IE_Pressed, this, &URPGUserWidgetBase::OnDefaultKeyDown).bExecuteWhenPaused = true;
		InputComponent->BindKey(EKeys::Left, IE_Pressed, this, &URPGUserWidgetBase::OnDefaultKeyLeft).bExecuteWhenPaused = true;
		InputComponent->BindKey(EKeys::Right, IE_Pressed, this, &URPGUserWidgetBase::OnDefaultKeyRight).bExecuteWhenPaused = true;

		InputComponent->BindKey(EKeys::E, IE_Pressed, this, &URPGUserWidgetBase::OnDefaultKeyOkay).bExecuteWhenPaused = true;;
		InputComponent->BindKey(EKeys::Q, IE_Pressed, this, &URPGUserWidgetBase::OnDefaultKeyCancel).bExecuteWhenPaused = true;;
	
		InputComponent->BindKey(EKeys::Tab, IE_Pressed, this, &URPGUserWidgetBase::OnDefaultKeyTab).bExecuteWhenPaused = true;

	}

	if (APlayerController* Controller = GetOwningPlayer())
	{
		Controller->DisableInput(Controller);
	}
}

void URPGUserWidgetBase::InputUnbindEvents()
{
	if (APlayerController* Controller = GetOwningPlayer())
	{
		Controller->EnableInput(Controller);
	}
}

void URPGUserWidgetBase::SetMousePosition()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector2D ViewportPosition;

	ViewportPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	if (UCanvasPanelSlot* CPSlot = Cast<UCanvasPanelSlot>(Slot)) {
		CPSlot->SetOffsets(ViewportPosition);
	}

}


