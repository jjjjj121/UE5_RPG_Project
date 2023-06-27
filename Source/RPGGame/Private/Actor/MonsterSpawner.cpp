// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MonsterSpawner.h"
#include "Actor/Monster.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	AMonster* MonsterUnit = GetWorld()->SpawnActor<AMonster>(AMonster::StaticClass(), SpawnLoaction, rotator, SpawnParms);

	MonsterUnit->SetUnit(MonsterTable,MonsterName_Key);
}


