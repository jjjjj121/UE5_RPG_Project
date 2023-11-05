// Fill out your copyright notice in the Description page of Project Settings.


#include "System/RPGGameInstance.h"

void URPGGameInstance::Init()
{
	if (DataTableManagerClass) {
		DataTableManager = NewObject<UDataTableManager>(this, DataTableManagerClass);
	}

	Super::Init();
}
