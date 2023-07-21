// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTN_Turn.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UBTTN_Turn : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTN_Turn(FObjectInitializer const& object_initializer);

	//Task가 실행될 때마다 실행되는 함수
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	class AMonster_AI* ControllingPawn;

	FRotator TargetRotator;
	float RotateSpeed = 2.5f;

};
