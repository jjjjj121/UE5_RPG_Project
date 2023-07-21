// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/EquipItem.h"
#include "Engine/DataTable.h"
#include "RPGGame/Structs.h"

AEquipItem::AEquipItem()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> EquipTableObject(TEXT("/Game/Data/DT_EquipItem.DT_EquipItem"));
	if (EquipTableObject.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("DATA TABLE SUCCEED"));
		ItemData = EquipTableObject.Object;
	}

}

void AEquipItem::BeginPlay()
{
	if (ItemData) {
		TArray<FName> RowList = ItemData->GetRowNames();
		FName RandomName = RowList[FMath::RandRange(0, RowList.Num() -1)];
		InitProperty(RandomName);

	}

	
}

void AEquipItem::InitProperty(FName RowName)
{
	FEquipItemTable* EquipData = ItemData->FindRow<FEquipItemTable>(RowName, FString(""));

	if (EquipData) {
		

		UE_LOG(LogTemp, Warning, TEXT("INIT PROPERTY"));
	}

}
