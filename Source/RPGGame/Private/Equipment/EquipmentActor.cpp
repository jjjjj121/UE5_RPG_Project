// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentActor.h"


AEquipmentActor::AEquipmentActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkelMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkelMesh->SetSimulatePhysics(false);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetSimulatePhysics(false);

	RootComponent = SkelMesh;
	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}


void AEquipmentActor::BeginPlay()
{
	Super::BeginPlay();
}

UMeshComponent* AEquipmentActor::GetMesh() const
{
	UMeshComponent* meshComponent = nullptr;

	if (SkelMesh->GetSkeletalMeshAsset())
	{
		meshComponent = SkelMesh;
	}
	else if (StaticMesh->GetStaticMesh())
	{
		meshComponent = StaticMesh;
	}

	return meshComponent;
}

void AEquipmentActor::SetID(FString NewID)
{
	ItemID = NewID;

}
