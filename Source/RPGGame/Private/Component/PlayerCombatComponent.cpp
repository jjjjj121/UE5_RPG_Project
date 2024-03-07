// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerCombatComponent.h"

#include "RPGGame/RPGGameCharacter.h"

UPlayerCombatComponent::UPlayerCombatComponent()
{



}

void UPlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnPlayer = Cast<ARPGGameCharacter>(GetOwner());
}


