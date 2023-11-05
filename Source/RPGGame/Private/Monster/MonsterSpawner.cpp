// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterSpawner.h"
#include "Monster/Monster_AI.h"
#include "RPGGame/Structs.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UDataTable> TableObject(TEXT("/Game/Data/NewDataTable.NewDataTable"));

	//if (TableObject.Succeeded()) {
	//	UE_LOG(LogTemp, Warning, TEXT("MONSTER DATA TABLE SUCCEED"));
	//	MonsterTable = TableObject.Object;
	//}

}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnUnit();
	
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawner::SpawnUnit()
{
	FActorSpawnParameters SpawnParms;
	SpawnParms.Owner = this;
	FRotator rotator;
	FVector SpawnLoaction = GetActorLocation();
	SpawnLoaction.Z -= 90.0f;

	AMonster_AI* MonsterUnit = GetWorld()->SpawnActor<AMonster_AI>(AMonster_AI::StaticClass(), SpawnLoaction, rotator, SpawnParms);

	MonsterUnit->SetUnit(MonsterTable, MonsterName_Key);
}


