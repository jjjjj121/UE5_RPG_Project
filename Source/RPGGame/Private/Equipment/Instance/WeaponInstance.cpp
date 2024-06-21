// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Instance/WeaponInstance.h"

#include "Library/RPGFunctionLibrary.h"
#include "Component/PlayerCombatComponent.h"

#include "Equipment/EquipmentActor.h"

#include "RPGGame/RPGGameCharacter.h"
#include "RPGGame/RPGGameAnimInstance.h"

UWeaponInstance::UWeaponInstance()
{
}

void UWeaponInstance::OnEquipped()
{
	Super::OnEquipped();

	//UE_LOG(LogTemp, Warning, TEXT("UWeaponInstance : OnEquipped"));

	//if (EquipAnimLayer) {
	//	ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld());
	//	Character->SetAnimLayer(EquipAnimLayer);
	//}

}

void UWeaponInstance::OnUnEquipped()
{
	Super::OnUnEquipped();

	//UE_LOG(LogTemp, Warning, TEXT("UWeaponInstance : UnEquipped"));

	//if (EquipAnimLayer) {
	//	ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld());
	//	Character->SetAnimLayer(nullptr);
	//}

}

void UWeaponInstance::OnHanded(bool EquipMotion)
{
	//UE_LOG(LogTemp, Warning, TEXT("UWeaponInstance : OnHanded _ %d"), EquipMotion);

	if (ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld())) {

		bEquiped = EquipMotion;

		TSubclassOf<UAnimInstance> NewAnimLayer = EquipMotion ? EquippedLayerset.EquipAnimLayer : EquippedLayerset.DefaultLayer;
		FAnimMontageSet NewMontageSet = EquippedMontageset;

		Character->SetAnimData(NewAnimLayer, NewMontageSet);


		///*Attach Weapon Bone*/
		if (EquipMotion) {
			AttachedSocket(EquipSocket);
		}

		/*Equip Montage Play*/
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
		float PlayRate = 1.f;

		UAnimMontage* NewMontage;
		NewMontage = EquipMotion ? EquippedMontageset.EquipAnim : EquippedMontageset.UnEquipAnim;
		AnimInstance->Montage_Play(NewMontage, PlayRate);

		AnimInstance->OnMontageEnded.AddDynamic(this, &UWeaponInstance::MontageEnded);
		bIsPlayingEquipMontage = true;




	}
}

void UWeaponInstance::MontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld())) {

		if (!bEquiped) {
			AttachedSocket(UnEquipSocket);
		}

		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
		AnimInstance->OnMontageEnded.Clear();

		//UE_LOG(LogTemp, Warning, TEXT("MONTAGE PLAY ENDED"));
	}

	bIsPlayingEquipMontage = false;

}

void UWeaponInstance::AttachedSocket(FName NewSocket)
{
	if (ARPGGameCharacter* Character = URPGFunctionLibrary::GetPlayerCharacter(GetWorld())) {
		USceneComponent* attachTarget = Character->GetMesh();
		FTransform AttachTransform;

		GetSpawnedActor()->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
		GetSpawnedActor()->AttachToComponent(attachTarget, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), NewSocket);

		//UE_LOG(LogTemp, Warning, TEXT("ATTACHED SOCKET : %s"), *NewSocket.ToString());
	}
}
