// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCombatComponent.generated.h"

class UBehaviorAnimData;
class ARPGGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGGAME_API UPlayerCombatComponent : public UActorComponent
{
	GENERATED_BODY()


private:
	UPROPERTY()
	ARPGGameCharacter* OwnPlayer;


private:
	//UPROPERTY(EditDefaultsOnly, Category = "WeaponAnim")
	//UBehaviorAnimData* DefaultAnimData;

	UPROPERTY(EditAnywhere, Category = "WeaponAnim")
	UBehaviorAnimData* WeaponAnimData;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponAnim")
	UBehaviorAnimData* ShieldAnimData;

public:	
	UPlayerCombatComponent();

public:
	virtual void BeginPlay() override;

public:
	//UFUNCTION(BlueprintCallable, Meta = (BlueprintThreadSafe))
	//UBehaviorAnimData* GetDefaultAnimData() const { return DefaultAnimData; }

	UFUNCTION(BlueprintCallable, Meta = (BlueprintThreadSafe))
	UBehaviorAnimData* GetWeaponAnimData() const { return WeaponAnimData; }
	UFUNCTION(BlueprintCallable, Meta = (BlueprintThreadSafe))
	UBehaviorAnimData* GetShieldAnimData() const { return ShieldAnimData; }

public:
	void SetWeaponAnimData(UBehaviorAnimData* NewEquipWeaponAnimData) { WeaponAnimData = NewEquipWeaponAnimData; }
	void SetShieldAnimData(UBehaviorAnimData* NewEquipWeaponAnimData) { ShieldAnimData = NewEquipWeaponAnimData; }


public:


	

};
