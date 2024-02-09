// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameHUD.h"
#include "Blueprint/UserWidget.h"

#include "RPGGameCharacter.h"
#include "RPGGamePlayerController.h"

void ARPGGameHUD::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ARPGGameCharacter>(GetOwningPawn());
	Controller = Cast<ARPGGamePlayerController>(GetOwner());

}

