// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInstance.generated.h"

/*Item °´Ã¼ Å¬·¡½º*/
UCLASS()
class RPGGAME_API UItemInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	class UItemDefinition* ItemDefinition;

	UPROPERTY()
	int32 ItemStack;
};
