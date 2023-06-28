// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Monster/MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "RPGGame/RPGGameCharacter.h"

//Black Board �� �ش� Key�� ������ �����ϱ� ���� - C++ �� Editor�� Blackboard ������ ����
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

	//������Ʈ ���� �� ����
	BT_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
	BlackBoard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponenet"));

	//Perception �ʱ�ȭ
	SetPerceptionSystem();

}

void AMonsterAIController::SetPerceptionSystem()
{
	//������Ʈ ���� �� ����(Sight Config)
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));
	
	//���� �ʱ�ȭ
	SightConfig->SightRadius = AISightRadius;								//���� �þ� �ݰ�
	SightConfig->LoseSightRadius = AILoseSightRadius;						//���� �� ���� �ִ� �ݰ�
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;				//�ֺ� �þ� ����
	SightConfig->SetMaxAge(AISightAge);										//������ �ڱ��� ���ӵǴ� �ð�
	SightConfig->AutoSuccessRangeFromLastSeenLocation = AILastSeenLocation;	//������ ���� ��ġ ����

	//���� ��� ����
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;			//��
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;		//��ȣ��
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;			//�߸�

	//������ ���� Perception�� ���
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	//�Լ� Bind
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnTargetDetected);

	UE_LOG(LogTemp, Warning, TEXT("SET PERCEPTION"));
}

void AMonsterAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (ARPGGameCharacter* const player = Cast<ARPGGameCharacter>(Actor)) {
		//Target ���� �� blackboard true�� ������Ʈ
		BlackBoard->SetValueAsBool(Key_CanSeePlayer, Stimulus.WasSuccessfullySensed());
		UE_LOG(LogTemp, Warning, TEXT("TARGET DETECTED"));
	}
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("AI POSSESS"));
	if (BlackBoard) {
		//Behavior Tree�� �ִ� Black Board �� �ʱ�ȭ ����
		BlackBoard->InitializeBlackboard(*BTree->BlackboardAsset);

		//���� ��ġ ������Ʈ
		BlackBoard->SetValueAsVector(Key_HomePos, InPawn->GetActorLocation());

	}

}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	//Behavior Tree ������ ���� (���ض� ai)
	if (!RunBehaviorTree(BTree)) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller couldn't run behavior tree"));
	}
	BT_Component->StartTree(*BTree);

}