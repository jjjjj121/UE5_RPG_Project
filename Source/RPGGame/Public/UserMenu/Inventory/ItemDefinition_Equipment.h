// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserMenu/Inventory/ItemDefinition.h"
#include "ItemDefinition_Equipment.generated.h"

/**
 *
 */
UCLASS()
class RPGGAME_API UItemDefinition_Equipment : public UItemDefinition
{
	GENERATED_BODY()

public:
	/*Equip에서만 추가될 것들*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		int32 Levellimit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EquipInfo)
		USkeletalMesh* ItemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float Defence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float STRlimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float DEXlimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float INTlimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float RepairPrice;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		float ItemSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EquipInfo)
		bool IsDualWield;

	UPROPERTY(EditDefaultsOnly, Category = ItemInfo)
		TSubclassOf<class UAttackBehavior> D_AttackBehavior;
};
