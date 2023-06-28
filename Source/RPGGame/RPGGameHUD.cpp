// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Widget/W_Inventory.h"

void ARPGGameHUD::BeginPlay()
{
	Super::BeginPlay();

	/*UUserWidget* HUDWidget = Cast<UUserWidget>(CreateWidget(GetWorld(), HUDWidgetclass));

	if (HUDWidget) {
		HUDWidget->AddToViewport();
	}*/

}
