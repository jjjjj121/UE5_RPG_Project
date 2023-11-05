// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UBTD_IsAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTD_IsAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
