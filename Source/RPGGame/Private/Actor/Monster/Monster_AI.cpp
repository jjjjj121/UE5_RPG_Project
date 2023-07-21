// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Monster/Monster_AI.h"
#include "RPGGame/Structs.h"
#include "Actor/Item/Item.h"
#include "Components/SkeletalMeshComponent.h"
#include "Actor/Monster/MonsterAIController.h"
#include "Actor/Monster/MonsterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMonster_AI::AMonster_AI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Mesh Position
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

}

// Called when the game starts or when spawned
void AMonster_AI::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	//GetCharacterMovement()->Acceleration
}

// Called every frame
void AMonster_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMonster_AI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster_AI::SetUnit(UDataTable* MonsterTable, FName MonsterName_)
{
	UE_LOG(LogTemp, Warning, TEXT("SET UNIT"));

	if (MonsterTable) {

		FMonsterTable* MData;

		//랜덤 스폰
		if (MonsterName_.IsNone()) {
			UE_LOG(LogTemp, Warning, TEXT("RANDOM UNIT SET"));
			TArray<FName> RowNames = MonsterTable->GetRowNames();
			FName RandomSeed = RowNames[FMath::RandRange(0, RowNames.Num())];
			MData = MonsterTable->FindRow<FMonsterTable>(RandomSeed, FString(""));

		}
		//지정 스폰
		else {
			MData = MonsterTable->FindRow<FMonsterTable>(MonsterName_, FString(""));
		}
	

		if (MData) {
			//Set Property
			Damage = MData->D_Damage;
			Defence = MData->D_Defence;
			Experience = MData->D_Experience;
			Level = MData->D_Level;
			MAXHP = MData->D_MAXHP;
			MAXMP = MData->D_MAXMP;
			MonsterID = MData->D_MonsterID;
			MonsterName = MData->D_MonsterName;
			Skill = MData->D_Skill;
			MonsterIcon = MData->MonsterIcon;
			MonsterMesh = MData->MonsterMesh;
			RootArray = MData->RootArray;

			//Set Mesh & Anim Instance
			GetMesh()->SetSkeletalMesh(MonsterMesh);
			GetMesh()->SetAnimClass(MData->MonsterAnimInstance);
			MonsterAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
			MonsterAnimInstance->SetBehavior(MData->Attack_Behavior);

			//Attack Montage Lamda Bind
			SetMontage_Lamda();

			//Set AI Controller
			AIControllerClass = MData->MonsterAIController;
			SpawnDefaultController();
			AI_Controller = Cast<AMonsterAIController>(GetController());
			
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("EEROR : Not Valid Monster Name"));
			Destroy();
		}
	}
}

void AMonster_AI::SetMontage_Lamda()
{
	if (MonsterAnimInstance) {
		MonsterAnimInstance->OnMontageEnded.AddDynamic(this, &AMonster_AI::OnAttackMontageEnded);
		//OnNextAttack 델리게이트에 람다 함수식 추가 -> Broadcast시 호출
		MonsterAnimInstance->OnNextAttack.AddLambda([this]()->void {
			CanNextCombo = false;
			if (IsAttacking) {
				if (IsComboInputOn) {
					AttackStartComboState();
					MonsterAnimInstance->JumpToAttackMontageSection(CurrentCombo);	//다음 콤보 Montage로 switching
					UE_LOG(LogTemp, Warning, TEXT("Attack Combo : %d"), CurrentCombo);
				}
			}
			});
		UE_LOG(LogTemp, Warning, TEXT("SET MONSTER ANIM CLASS"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("MONSTER ANIM CLASS NOT VALID"));
	}

}

void AMonster_AI::DropItem()
{
	if (RootArray.Num()) {

		uint8 RandomSeed;
		RandomSeed = FMath::RandRange(0, 100);
		//EItemType RandomType = static_cast<EItemType>(RandomSeed);

		for (FRootArrayData RootData : RootArray) {
			if (RootData.DropRate <= RandomSeed) {
				TSubclassOf<AItem> ItemClass = RootData.RootItemclass;
				AItem* RootItem = NewObject<AItem>(this, ItemClass->StaticClass());

				RootItem->SpawnItem();


			}
		}
	}
}


void AMonster_AI::Attack()
{
	//AI_Controller->EnableSight(false);
	AI_Controller->SetKey_IsAttacking(true);
	
	//공격 중인경우
	if (IsAttacking) {
		//다음 콤보가 있는 경우
		if (CanNextCombo) {
			IsComboInputOn = true;
		}
	}
	//첫 Attack 콤보인 경우
	else {
		AttackStartComboState();
		MonsterAnimInstance->PlayAttackMontage();	//Montage 실행
		IsAttacking = true;
	}
}

bool AMonster_AI::GetIsAttacking()
{
	return IsAttacking;
}


void AMonster_AI::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	//AI_Controller->EnableSight(true);
	AI_Controller->SetKey_IsAttacking(false);

	IsAttacking = false;
	AttackEndComboState();
	UE_LOG(LogTemp, Warning, TEXT("MONTAGE END"));
}

void AMonster_AI::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MonsterAnimInstance->GetMaxCombo());
}

void AMonster_AI::AttackEndComboState()
{
	CanNextCombo = false;
	IsComboInputOn = false;
	CurrentCombo = 0;
}