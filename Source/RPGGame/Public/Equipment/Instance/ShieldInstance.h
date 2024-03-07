// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/EquipmentInstance.h"
#include "ShieldInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UShieldInstance : public UEquipmentInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	class UBehaviorAnimData* BehaviorAnim;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Armor;

public:
	UShieldInstance();

	virtual void OnEquipped() override;
	virtual void OnUnEquipped() override;

public:
	const float GetArmor() const { return Armor; }
};
