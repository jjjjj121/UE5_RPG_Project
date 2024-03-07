// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/EquipmentInstance.h"
#include "Library/AnimEnumLibrary.h"
#include "WeaponInstance.generated.h"

class UBehaviorAnimData;
class UAnimMontage;

UCLASS()
class RPGGAME_API UWeaponInstance : public UEquipmentInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EOverlayType OverlayType;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UBehaviorAnimData* BehaviorAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	TSubclassOf<UAnimInstance> EquipAnimLayer;

	//UPROPERTY(EditDefaultsOnly, Category = "Anim")
	//FAnimLayerSelectSet EquippedAnimset;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* EquipAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* UnEquipAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* AttackAnim;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	float Damage;

public:
	UWeaponInstance();

	virtual void OnEquipped() override;
	virtual void OnUnEquipped() override;

public:
	FORCEINLINE EOverlayType GetOverlayType() const { return OverlayType; }

	const float GetDamage() const { return Damage; }
};
