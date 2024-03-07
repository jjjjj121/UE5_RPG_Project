// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentInstance.h"

#include "RPGGame/RPGGameCharacter.h"
#include "RPGGame/RPGGamePlayerController.h"

#include "Equipment/EquipmentActor.h"
#include "Equipment/EquipmentDefinition.h"

void UEquipmentInstance::SpawnEquipmentActor(const FEquipmentActorToSpawn& _ActorToSpawn)
{
	if (IsValid(_ActorToSpawn.ActorToSpawn) == false)
	{
		return;
	}
	
	ARPGGamePlayerController* OwningController = Cast<ARPGGamePlayerController>(GetOuter());
	ARPGGameCharacter* owingCharacter = Cast<ARPGGameCharacter>(OwningController->GetCharacter());

	if (owingCharacter)
	{
		USceneComponent* attachTarget = owingCharacter->GetMesh();

		SpawnedActor = owingCharacter->GetWorld()->SpawnActorDeferred<AEquipmentActor>(_ActorToSpawn.ActorToSpawn, FTransform::Identity, owingCharacter);
		if (SpawnedActor)
		{
			SpawnedActor->FinishSpawning(FTransform::Identity, true);
			SpawnedActor->SetActorRelativeTransform(_ActorToSpawn.AttachTransform);
			SpawnedActor->AttachToComponent(attachTarget, FAttachmentTransformRules::KeepRelativeTransform, _ActorToSpawn.AttachSocket);
		}
	}
}

void UEquipmentInstance::DestroyEquipmentActor()
{
	if (SpawnedActor){
		SpawnedActor->Destroy();
	}
	
}

void UEquipmentInstance::OnEquipped()
{
	/*Stat update부분 들어가면 될 듯*/
}

void UEquipmentInstance::OnUnEquipped()
{
}

void UEquipmentInstance::SetInstigator(UObject* _Instigator)
{
	Instigator = _Instigator;
}
