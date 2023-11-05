// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTS_Detect.h"
#include "Monster/MonsterAIController.h"
#include "RPGGame/RPGGameCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"


UBTS_Detect::UBTS_Detect(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Detect");
	//tick 간격
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
	float DetectRadius = 500.f;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParams(NAME_None, false, ControllingPawn);
	bool Result = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParams);


	if (Result) {
		for (auto OverlapResult : OverlapResults) {
			ARPGGameCharacter* Player = Cast<ARPGGameCharacter>(OverlapResult.GetActor());

			//컨트롤러도 플레이어의 컨트롤러인지 이중 체크
			if (Player && Player->GetController()->IsPlayerController()) {
				
				//Target update
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::Key_Target, Player);

				//Debug
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(World, Player->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Player->GetActorLocation(), FColor::Blue, false, 0.2f);

				return;
			}

		}
	}
	//감지 구역에서 벗어난 경우
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::Key_Target, nullptr);
		UE_LOG(LogTemp, Warning, TEXT(""));
		
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}
