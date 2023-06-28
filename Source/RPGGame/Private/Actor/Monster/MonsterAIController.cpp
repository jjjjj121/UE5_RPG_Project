// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Monster/MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "RPGGame/RPGGameCharacter.h"

//Black Board 에 해당 Key로 변수에 접근하기 위함 - C++ 과 Editor의 Blackboard 변수를 연결
const FName AMonsterAIController::Key_HomePos(TEXT("HomePos"));
const FName AMonsterAIController::Key_Patrol(TEXT("PatrolPos"));
const FName AMonsterAIController::Key_TargetLocation(TEXT("TargetLocation"));
const FName AMonsterAIController::Key_CanSeePlayer(TEXT("CanSeePlayer"));
const FName AMonsterAIController::Key_IsPlayerInMeleeRange(TEXT("IsPlayerInMeleeRange"));

AMonsterAIController::AMonsterAIController(FObjectInitializer const& object_initializer)
{
	//Behavior Tree Init
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_Object(TEXT("/Game/Data/BT_Monster.BT_Monster"));
	if (BT_Object.Succeeded()) {
		BTree = BT_Object.Object;
		UE_LOG(LogTemp, Warning, TEXT("Behavior Tree Bind Succeed"));
	}

	//컴포넌트 생성 및 대입
	BT_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
	BlackBoard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponenet"));

	//Perception 초기화
	SetPerceptionSystem();

}

void AMonsterAIController::SetPerceptionSystem()
{
	//컴포넌트 생성 및 대입(Sight Config)
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));
	
	//변수 초기화
	SightConfig->SightRadius = AISightRadius;								//감지 시야 반경
	SightConfig->LoseSightRadius = AILoseSightRadius;						//감지 후 인지 최대 반경
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;				//주변 시야 각도
	SightConfig->SetMaxAge(AISightAge);										//생성된 자극이 지속되는 시간
	SightConfig->AutoSuccessRangeFromLastSeenLocation = AILastSeenLocation;	//마지막 감지 위치 범위

	//감지 대상 설정
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;			//적
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;		//우호적
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;			//중립

	//설정한 감각 Perception에 등록
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	//함수 Bind
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnTargetDetected);

	UE_LOG(LogTemp, Warning, TEXT("SET PERCEPTION"));
}

void AMonsterAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (ARPGGameCharacter* const player = Cast<ARPGGameCharacter>(Actor)) {
		//Target 감지 시 blackboard true로 업데이트
		BlackBoard->SetValueAsBool(Key_CanSeePlayer, Stimulus.WasSuccessfullySensed());
		UE_LOG(LogTemp, Warning, TEXT("TARGET DETECTED"));
	}
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("AI POSSESS"));
	if (BlackBoard) {
		//Behavior Tree에 있는 Black Board 로 초기화 진행
		BlackBoard->InitializeBlackboard(*BTree->BlackboardAsset);

		//시작 위치 업데이트
		BlackBoard->SetValueAsVector(Key_HomePos, InPawn->GetActorLocation());

	}

}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	//Behavior Tree 실행을 시작 (일해라 ai)
	if (!RunBehaviorTree(BTree)) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller couldn't run behavior tree"));
	}
	BT_Component->StartTree(*BTree);

}
