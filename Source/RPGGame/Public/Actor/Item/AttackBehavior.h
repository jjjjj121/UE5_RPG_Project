// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttackBehavior.generated.h"


/**
 * 
 */
UCLASS()
class RPGGAME_API UAttackBehavior : public UObject
{
	GENERATED_BODY()
	

public:
	UAnimInstance* ParentAnimInstance;
	int32 MaxCombo;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowprivateAccess = true))
		UAnimMontage* AttackMontage;

public:
	virtual void PlayAttackMontage();
	/*Change Montage Section*/
	virtual void JumpToAttackMontageSection(int32 NewSection);
	/*Get Montage Section Name*/
	virtual FName GetAttackMontageSectionName(int32 Section);

};
