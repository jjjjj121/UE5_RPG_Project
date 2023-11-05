// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/DataTableManager.h"
#include "SubSystem/RPGWidgetSubSystem.h"
#include "RPGGameInstance.generated.h"

#define RPG_GAMEINSTANCE(world) (Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(world)))
#define DATATABLE_MANAGER(world) (RPG_GAMEINSTANCE(world)->GetDataTableManager())

#define WIDGET_SUBSYSTEM(world) (RPG_GAMEINSTANCE(world)->GetSubsystem<URPGWidgetSubSystem>())
/**
 * 
 */
UCLASS()
class RPGGAME_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void Init() override;


public:
	UFUNCTION(BlueprintPure, Category = "Manager")
	UDataTableManager* GetDataTableManager() { return DataTableManager; }
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Manager")
	TSubclassOf<UDataTableManager> DataTableManagerClass;
private:
	UPROPERTY(Transient)
	UDataTableManager* DataTableManager;


};
