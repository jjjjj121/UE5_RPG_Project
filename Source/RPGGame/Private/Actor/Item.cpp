// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::SpawnItem()
{
	//uint8 RandomSeed;
	//RandomSeed = FMath::RandRange(0, 3);
	//EItemType RandomType = static_cast<EItemType>(RandomSeed);
	//

	//if (RandomType == EItemType::Consumable) {
	//	UE_LOG(LogTemp, Warning, TEXT("Consumable"));
	//}
	//else if (RandomType == EItemType::Equip) {
	//	UE_LOG(LogTemp, Warning, TEXT("Equip"));
	//	
	//}
	//else if (RandomType == EItemType::Jewel) {
	//	UE_LOG(LogTemp, Warning, TEXT("Jewel"));
	//}
	//else if (RandomType == EItemType::Material) {
	//	UE_LOG(LogTemp, Warning, TEXT("Material"));
	//}


}
