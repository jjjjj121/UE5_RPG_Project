// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/Instance/WeaponInstance.h"
#include "MeleeWeaponInstance.generated.h"

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FComboData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* HitEffect;
};


UCLASS()
class RPGGAME_API UMeleeWeaponInstance : public UWeaponInstance
{
	GENERATED_BODY()
	
public:
	UMeleeWeaponInstance();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combo"/*, meta = (DisplayPriority = 1)*/)
	TArray<FComboData> ComboDatas;

public:
	FORCEINLINE const FComboData* GetComboData(int32 _Index) const { return &ComboDatas[_Index]; }

};
