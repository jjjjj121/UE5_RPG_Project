// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Instance/WeaponInstance.h"

UWeaponInstance::UWeaponInstance()
{
}

void UWeaponInstance::OnEquipped()
{
	UE_LOG(LogTemp, Warning, TEXT("UWeaponInstance : OnEquipped"));
	//if (behavioranim != nullptr) {

	//}
}

void UWeaponInstance::OnUnEquipped()
{
}
