// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Monster/BTS_Detect.h"
#include "Actor/Monster/MonsterAIController.h"

UBTS_Detect::UBTS_Detect(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Detect");
	//tick АЃАн
	Interval = 1.0f;
}

void UBTS_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	auto ControllingPawn = Controller->GetPawn();
	if (ControllingPawn == nullptr) return;

	UWorld* World = ControllingPawn->GetWorld();
	if (World == nullptr) return;

	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f;




}
