// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster_AI.h"
#include "RPGGame/Structs.h"
#include "Components/SkeletalMeshComponent.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

#include "Engine/DamageEvents.h"
#include "DamageType/DamageType_Base.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Library/RPGFunctionLibrary.h"
#include "Library/RPGWidgetFunctionLibrary.h"
#include "Library/WidgetEnumLibrary.h"

#include "UserMenu/Inventory/ItemInstance.h"
#include "UserMenu/Inventory/ItemDefinition.h"
#include "UserMenu/AC_UserMenuComponent.h"

#include "RPGGame/RPGGameCharacter.h"
#include "RPGGame/RPGGamePlayerController.h"

// Sets default values
AMonster_AI::AMonster_AI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set Mesh Position
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	//set Collision
	GetMesh()->SetCollisionProfileName(FName("Monster"));
	GetMesh()->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void AMonster_AI::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = 250.f;

	//Player Tag 추가
	Tags.Add(FName(TEXT("Monster")));

	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	//GetCharacterMovement()->Acceleration
}

void AMonster_AI::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	//ARPGGameCharacter* Player = Cast<ARPGGameCharacter>(OtherActor);
	////Monster가 Player를 Attack 중일때만 적용
	//if (Player && IsAttacking) {
	//	//Overlap Event가 여러번 호출되므로 한 번만 데미지 적용 하기 위함.
	//	if (!bBeDamaged) {
	//		UE_LOG(LogTemp, Warning, TEXT("Damage !"));
	//		bBeDamaged = true;
	//	}
	//}
}

// Called every frame
void AMonster_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("ISAttacking : %d"), IsAttacking);
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
			//MonsterAnimation = MData->MonsterAnimation;

			CurHP = MAXHP;
			CurMP = MAXMP;

			//Set Mesh & Anim Instance
			GetMesh()->SetSkeletalMesh(MonsterMesh);
			GetMesh()->SetAnimClass(MData->MonsterAnimInstance);
			MonsterAnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
			//MonsterAnimInstance->SetBehavior(MData->Attack_Behavior);
			MonsterAnimInstance->SetAnimationProperty(MData->MonsterAnimation);

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
		//MonsterAnimInstance->OnMontageEnded.AddDynamic(this, &AMonster_AI::OnAttackMontageEnded);
		//OnNextAttack 델리게이트에 람다 함수식 추가 -> Broadcast시 호출
		MonsterAnimInstance->OnNextAttack.AddLambda([this]()->void {
			CanNextCombo = false;
			if (CurrentCombo > 0) {
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
			}
		}
	}
}


void AMonster_AI::Attack()
{
	//AI_Controller->EnableSight(false);
	AI_Controller->SetKey_IsAttacking(true);

	//공격 중인경우
	if (CurrentCombo > 0) {
		//다음 콤보가 있는 경우
		if (CanNextCombo) {
			IsComboInputOn = true;
		}
	}
	//첫 Attack 콤보인 경우
	else {
		AttackStartComboState();
		MonsterAnimInstance->OnMontageEnded.AddDynamic(this, &AMonster_AI::OnAttackMontageEnded);
		IsAttacking = true;
		MonsterAnimInstance->PlayAttackMontage();	//Montage 실행
	}
}

void AMonster_AI::InitAttack()
{
	AI_Controller->SetKey_IsAttacking(false);
	IsAttacking = false;
	AttackEndComboState();

	MonsterAnimInstance->OnMontageEnded.RemoveDynamic(this, &AMonster_AI::OnAttackMontageEnded);
}

bool AMonster_AI::GetIsAttacking()
{
	return IsAttacking;
}


void AMonster_AI::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	InitAttack();
}

void AMonster_AI::OnReactMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnReactMontageEnded"));

	AI_Controller->GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Key_CanSeePlayer, true);

	bRunningHit = false;
	MonsterAnimInstance->OnMontageEnded.RemoveDynamic(this, &AMonster_AI::OnReactMontageEnded);
}

float AMonster_AI::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float NewDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurHP = FMath::Clamp<float>(CurHP - DamageAmount, 0, MAXHP);

	UE_LOG(LogTemp, Warning, TEXT("Monster CUR HP : %f"), CurHP);
	bRunningHit = true;

	if (CurHP <= 0) {
		IsDead = true;
		AI_Controller->GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Key_IsDead, true);
	}

	/*Damage 받으면 공격자에게 어그로*/
	AI_Controller->GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::Key_Target, DamageCauser);

	/*Hit 방향 계산*/
	FRotator Delta_A = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), DamageCauser->GetActorLocation());
	FRotator Delta_B = GetActorRotation();
	FRotator Delta_Rotator = UKismetMathLibrary::NormalizedDeltaRotator(Delta_A, Delta_B);
	int32 Direction_Index = CalculateDirectionIndex(Delta_Rotator.Yaw);

	/*DamageType으로 약/강공 인지 체크*/
	// If you need the DamageType object like in blueprint, this is how you do it:
	UDamageType const* const DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();
	const UDamageType_Base* MyDamageType = Cast<UDamageType_Base>(DamageTypeCDO);

	HitReaction(Direction_Index, MyDamageType == nullptr ? false : MyDamageType->IsCharged);


	return NewDamage;
}

void AMonster_AI::AttackStartComboState()
{
	//CanNextCombo = true;
	IsComboInputOn = false;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MonsterAnimInstance->GetMaxCombo());
}

void AMonster_AI::AttackEndComboState()
{
	//CanNextCombo = false;
	IsComboInputOn = false;
	CurrentCombo = 0;
}

int32 AMonster_AI::CalculateDirectionIndex(float Direction)
{
	/*Hit Front*/
	if (Direction >= -45.f && Direction <= 45.f) {
		UE_LOG(LogTemp, Warning, TEXT("MONSTER HTI Front"));
		return 0;
	}
	/*Hit Right*/
	else if (Direction > 45.f && Direction <= 135.f) {
		UE_LOG(LogTemp, Warning, TEXT("MONSTER HTI Right"));
		return 1;
	}
	/*Hit Left*/
	else if (Direction >= -135.f && Direction < -45.f) {
		UE_LOG(LogTemp, Warning, TEXT("MONSTER HTI Left"));
		return 2;
	}
	/*Hit Back*/
	else if ((Direction >= -180.f && Direction < -135.f) || (Direction >= 135.f && Direction < 180.f)) {
		UE_LOG(LogTemp, Warning, TEXT("MONSTER HTI Back"));
		return 3;
	}

	/*Error*/
	return -1;
}

void AMonster_AI::HitReaction(int32 SectionIndex, bool IsCharged)
{
	UAnimMontage* React_Montage = nullptr;

	/*Montage SectionName 계산*/
	FName SectionName = FName(*FString::Printf(TEXT("Reaction%d"), SectionIndex));
	
	if (!IsDead){
		if (IsCharged) {
			React_Montage = MonsterAnimInstance->MonsterAnimation.Charged_Hit_Reaction_Montages;
			UE_LOG(LogTemp, Warning, TEXT("Charged_Hit_Reaction_Montages"));
		}
		else {
			React_Montage = MonsterAnimInstance->MonsterAnimation.Basic_Hit_Reaction_Montages;
			UE_LOG(LogTemp, Warning, TEXT("Basic_Hit_Reaction_Montages"));
		}

		MonsterAnimInstance->Montage_Play(React_Montage);
		MonsterAnimInstance->Montage_JumpToSection(SectionName, React_Montage);

		MonsterAnimInstance->OnMontageEnded.Clear();
		MonsterAnimInstance->OnMontageEnded.AddDynamic(this, &AMonster_AI::OnReactMontageEnded);

	}
	else {
		React_Montage = MonsterAnimInstance->MonsterAnimation.Death_Reaction_Montages;
		UE_LOG(LogTemp, Warning, TEXT("Death_Reaction_Montages"));

		MonsterAnimInstance->Montage_Play(React_Montage);
		MonsterAnimInstance->Montage_JumpToSection(SectionName, React_Montage);

		UE_LOG(LogTemp, Warning, TEXT("SECTION LENGTH : %f"), React_Montage->GetSectionLength(1));
		const float TriggerRagdollTime = React_Montage->GetSectionLength(SectionIndex) - 0.1f;
		
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
		GetMesh()->bBlendPhysics = true;

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMonster_AI::SetRagdollPhysics, FMath::Max(0.1f, TriggerRagdollTime), false);

		SetRootItems();

	}

}

void AMonster_AI::SetRootItems()
{
	if (RootArray.Num()) {
		for (FRootArrayData RootItemData : RootArray) {
			for (int i = 0; i < RootItemData.RollDice; ++i) {
				float Dice = FMath::RandRange(0.f, 1.f);
				//UE_LOG(LogTemp, Warning, TEXT("DICE : %f"), Dice);
				if (Dice <= RootItemData.DropRate) {
					RootItemData.ItemNum++;
				}
			}
			if (RootItemData.ItemNum) {
				UItemInstance* NewInstance = NewObject<UItemInstance>(this);
				NewInstance->ItemDefinition = NewObject<UItemDefinition>(this);
				NewInstance->InitInstance(RootItemData.RootItemID);
				NewInstance->ItemStack = RootItemData.ItemNum;

				RootItems.Add(NewInstance);
			}
		}
	}
}

void AMonster_AI::SetRagdollPhysics()
{
	UE_LOG(LogTemp, Warning, TEXT("RAGDOLL"));

	//Tags.Add(FName(TEXT("Dead")));

	// initialize physics/etc
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	//GetMesh()->bBlendPhysics = true;

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->SetComponentTickEnabled(false);

	SetLifeSpan(60.0f);
}

bool AMonster_AI::IsAvailableInteraction_Implementation() const
{
	return IsDead && RootItems.Num();
}

bool AMonster_AI::ExecuteInteraction_Implementation(AActor* InteractionTarget, UItemInstance* NewItemInstance)
{
	UE_LOG(LogTemp, Warning, TEXT("[AMonster_AI] : ExecuteInteraction_Implementation"));

	// TouchActor의 인벤토리에 추가
	if (ACharacter* Character = Cast<ACharacter>(TouchActor))
	{
		if (ARPGGamePlayerController* PlayerController = URPGFunctionLibrary::GetPlayerController(Character))
		{
			if (UAC_UserMenuComponent* InventoryComponent = PlayerController->FindComponentByClass<UAC_UserMenuComponent>())
			{

				if (InventoryComponent->AddItemToInventory(NewItemInstance))
				{
					int32 Index = RootItems.Find(NewItemInstance);
					RootItems.RemoveAt(Index);

					return true;
				}
			}
		}
	}

	return false;
}

void AMonster_AI::StopInteration_Implementation(AActor* InteractionTarget)
{
	UE_LOG(LogTemp, Warning, TEXT("[AMonster_AI] : StopInteration_Implementation"));
}

void AMonster_AI::SetTouchActor_Implementation(AActor* NewTouchActor)
{
	TouchActor = Cast<ARPGGameCharacter>(NewTouchActor);
}

TArray<UItemInstance*> AMonster_AI::GetRootItemList_Implementation()
{
	return RootItems;
}

FName AMonster_AI::GetInteractionActorName_Implementation()
{
	return FName(MonsterName);
}

FVector AMonster_AI::GetInteractionWidgetLocation_Implementation()
{
	FVector WidgetLocation = GetMesh()->GetSocketLocation(FName("Spine"));
	WidgetLocation.Z += 30.f;

	return WidgetLocation;
}
