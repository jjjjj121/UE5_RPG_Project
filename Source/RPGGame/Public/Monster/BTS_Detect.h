// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_Detect.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UBTS_Detect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTS_Detect(FObjectInitializer const& object_initializer);

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
};
