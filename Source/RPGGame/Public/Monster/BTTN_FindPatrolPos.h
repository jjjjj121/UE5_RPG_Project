// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTN_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UBTTN_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
		float Search_radius = 500.0f;

public:
	UBTTN_FindPatrolPos(FObjectInitializer const& object_initializer);

	//Task가 실행될 때마다 실행되는 함수
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;



};
