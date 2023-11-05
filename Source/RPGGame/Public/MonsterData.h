// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterData.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UMonsterData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UAnimInstance* ParentAnimInstance;

	int32 MaxCombo;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowprivateAccess = true))
		UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere)
		TMap<int32, UAnimMontage*> Basic_Hit_Reaction_Montages;

	UPROPERTY(EditAnywhere)
		TMap<int32, UAnimMontage*> Charged_Hit_Reaction_Montages;

	UPROPERTY(EditAnywhere)
		TMap<int32, UAnimMontage*> Death_Reaction_Montages;

public:
	virtual void PlayAttackMontage();
	/*Change Montage Section*/
	virtual void JumpToAttackMontageSection(int32 NewSection);
	/*Get Montage Section Name*/
	virtual FName GetAttackMontageSectionName(int32 Section);

};
