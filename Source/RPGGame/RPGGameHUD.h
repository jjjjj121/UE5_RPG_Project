// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPGGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API ARPGGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> HUDWidgetclass;
	
	UPROPERTY(BlueprintReadOnly, Category = "Widget")
	class UW_HUD* HUDWidget;

	class ARPGGameCharacter* Player;

	class ARPGGamePlayerController* Controller;

public:
	void BeginPlay() override;

public:
	bool bRootItem;
};
