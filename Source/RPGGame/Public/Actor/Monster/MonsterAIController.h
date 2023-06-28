// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BT_Component;

	//BehaviorTree
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BTree;

	//Perception º¯¼ö
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AISightRadius = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AILoseSightRadius = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AIFieldOfView = 90.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AISightAge = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AILastSeenLocation = 900.f;

	//BlackBorad
	class UBlackboardComponent* BlackBoard;

	//Sense config Sight
	class UAISenseConfig_Sight* SightConfig;

public:
	//Blackboard Key
	static const FName Key_HomePos;
	static const FName Key_Patrol;
	static const FName Key_TargetLocation;
	static const FName Key_CanSeePlayer;
	static const FName Key_IsPlayerInMeleeRange;


public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	AMonsterAIController(FObjectInitializer const& object_initializer);

public:
	UFUNCTION()
	void SetPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, struct FAIStimulus const Stimulus);
};
