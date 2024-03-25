// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Instance/ShieldInstance.h"

#include "RPGGame/RPGGameCharacter.h"

#include "Library/RPGFunctionLibrary.h"

#include "Component/PlayerCombatComponent.h"

UShieldInstance::UShieldInstance() : Armor(0)
{
}

void UShieldInstance::OnEquipped()
{
	Super::OnEquipped();

	UE_LOG(LogTemp, Warning, TEXT("UWeaponInstance : OnEquipped"));
	if (BehaviorAnim != nullptr) {
		ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld());

		if (UPlayerCombatComponent* CombatComponent = Character->FindComponentByClass<UPlayerCombatComponent>()) {
			//CombatComponent->SetShieldAnimData(BehaviorAnim);
		}


		//URPGGameAnimInstance* AnimInstance = Cast<URPGGameAnimInstance>(Character->GetMesh()->GetAnimInstance());
		//AnimInstance->SetEquipAnimData(BehaviorAnim);
	}
}

void UShieldInstance::OnUnEquipped()
{
	Super::OnUnEquipped();
}
