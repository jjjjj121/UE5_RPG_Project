// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInstance.generated.h"

class UItemDefinition;

/*Item °´Ã¼ Å¬·¡½º*/
UCLASS()
class RPGGAME_API UItemInstance : public UObject
{
	GENERATED_BODY()

public:
	UItemInstance();

public:
	UPROPERTY(VisibleAnywhere)
	UItemDefinition* ItemDefinition;

	UPROPERTY(VisibleAnywhere)
	int32 ItemStack = 1;

	UPROPERTY(VisibleAnywhere)
	FString ItemID;

public:
	void InitInstance(FString ID);
};
