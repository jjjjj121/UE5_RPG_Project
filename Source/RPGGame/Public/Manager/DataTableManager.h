// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGame/Structs.h"
#include "DataTableManager.generated.h"

class UDataTable;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class RPGGAME_API UDataTableManager : public UObject
{
	GENERATED_BODY()
	
#pragma region Item
public:
	FItemData* GetItemData(FString ItemDataID);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Table")
	UDataTable* ItemDataTable;
#pragma endregion



#pragma region Widget
public:
	TSubclassOf<UUserWidget> GetWidgetClassWithName(FName WidgetName);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Table")
		UDataTable* WidgetDataTable;

#pragma endregion
};
