// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Instance/WeaponInstance.h"

#include "Library/RPGFunctionLibrary.h"
#include "Component/PlayerCombatComponent.h"

#include "RPGGame/RPGGameCharacter.h"
#include "RPGGame/RPGGameAnimInstance.h"

UWeaponInstance::UWeaponInstance()
{
}

void UWeaponInstance::OnEquipped()
{
	Super::OnEquipped();

	UE_LOG(LogTemp, Warning, TEXT("UWeaponInstance : OnEquipped"));

	if (EquipAnimLayer) {
		ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld());
		Character->SetAnimLayer(EquipAnimLayer);
	}

	//if (BehaviorAnim != nullptr) {
	//	ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld());
	//	if (UPlayerCombatComponent* CombatComponent = Character->FindComponentByClass<UPlayerCombatComponent>()) {
	//		CombatComponent->SetWeaponAnimData(BehaviorAnim);
	//	}


	//	//URPGGameAnimInstance* AnimInstance = Cast<URPGGameAnimInstance>(Character->GetMesh()->GetAnimInstance());
	//	//AnimInstance->SetEquipAnimData(BehaviorAnim);
	//}
}

void UWeaponInstance::OnUnEquipped()
{
	Super::OnUnEquipped();

	UE_LOG(LogTemp, Warning, TEXT("UWeaponInstance : UnEquipped"));

	if (EquipAnimLayer) {
		ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld());
		Character->SetAnimLayer(nullptr);
	}

}
