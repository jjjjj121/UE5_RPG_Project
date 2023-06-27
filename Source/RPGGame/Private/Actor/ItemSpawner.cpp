// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ItemSpawner.h"
#include "Actor/Item.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::RandomSpawn(TArray<FRootArrayData> RootArray)
{
	if (RootArray.Num()) {
		TArray<TSubclassOf<AItem>> ResultArray;

		for (FRootArrayData RootItem : RootArray) {
			float randomseed = FMath::RandRange(0.0f, 100.0f);
			if (randomseed < RootItem.DropRate) {
				ResultArray.Add(RootItem.RootItemclass);
			}
		}

		for (TSubclassOf<AItem> Itemclass : ResultArray) {
			AItem* Item = Itemclass.GetDefaultObject();

			Item->SpawnItem();
		}
	}

}

