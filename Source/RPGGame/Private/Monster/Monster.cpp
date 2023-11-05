// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"

// Sets default values
AMonster::AMonster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::SetUnit(UDataTable* MonsterTable, FName MonsterName_)
{
	UE_LOG(LogTemp, Warning, TEXT("SET UNIT"));

	if (MonsterTable) {

		FMonsterTable* MData;

		//랜덤 스폰
		if (MonsterName_.IsNone()) {
			UE_LOG(LogTemp, Warning, TEXT("RANDOM UNIT SET"));
			TArray<FName> RowNames = MonsterTable->GetRowNames();
			FName RandomSeed = RowNames[FMath::RandRange(0, RowNames.Num())];
			MData = MonsterTable->FindRow<FMonsterTable>(RandomSeed, FString(""));

		}
		//지정 스폰
		else {
			MData = MonsterTable->FindRow<FMonsterTable>(MonsterName_, FString(""));
		}

		if (MData) {
			Damage = MData->D_Damage;
			Defence = MData->D_Defence;
			Experience = MData->D_Experience;
			Level = MData->D_Level;
			MAXHP = MData->D_MAXHP;
			MAXMP = MData->D_MAXMP;
			MonsterID = MData->D_MonsterID;
			MonsterName = MData->D_MonsterName;
			Skill = MData->D_Skill;
			ItemIcon = MData->MonsterIcon;
			ItemMesh = MData->MonsterMesh;
			RootArray = MData->RootArray;

			UE_LOG(LogTemp, Warning, TEXT("SET UNIT : %s"), *MonsterName);

			auto owner = GetOwner();

			UE_LOG(LogTemp, Warning, TEXT("Get Owner : %s"), *owner->GetName());

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("EEROR : Not Valid Monster Name"));
			Destroy();
		}
	}
}

void AMonster::DropItem()
{
	if (RootArray.Num()) {

		uint8 RandomSeed;
		RandomSeed = FMath::RandRange(0, 100);

		for (FRootArrayData RootData : RootArray) {
			if (RootData.DropRate <= RandomSeed) {
			
			}
		}
	}

}

