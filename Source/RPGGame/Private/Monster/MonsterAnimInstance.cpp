// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterAnimInstance.h"
#include "Monster/Monster_AI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MonsterData.h"


UMonsterAnimInstance::UMonsterAnimInstance(FObjectInitializer const& object_initializer)
{

}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningCharacter) {
		UpdateAnimProperty();
	}
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AMonster_AI>(GetOwningActor());
	if (OwningCharacter) {
		MovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UMonsterAnimInstance::UpdateAnimProperty()
{
	//set velocity & direction
	Velocity = MovementComponent->Velocity;
	CurDirection = CalculateDirection(MovementComponent->Velocity, OwningCharacter->GetActorRotation());

	//2D Size == vector length XY
	CurrentPawnSpeed = Velocity.Size2D();

	//MovementComponent->UseAccelerationForPathFollowing(true);
	FVector Acceleration = MovementComponent->GetCurrentAcceleration();

	if (/*Acceleration != FVector(0.0f, 0.0f, 0.0f) &&*/ CurrentPawnSpeed > 3.0f) {
		ShouldMove = true;
	}
	else {
		ShouldMove = false;
	}

}


void UMonsterAnimInstance::PlayAttackMontage()
{
	if (!IsAnyMontagePlaying()) {
		Montage_Play(MonsterAnimation.AttackMontage, 1.0f);
	}
}

void UMonsterAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	UE_LOG(LogTemp, Warning, TEXT("Attack Combo222222 : %d"), NewSection);
	Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), MonsterAnimation.AttackMontage);
}

void UMonsterAnimInstance::AnimNotify_AttackHitNotify()
{
	//해당 델리게이트 안에 있는 모든 함수 실행
	OnAttackHit.Broadcast();
}

void UMonsterAnimInstance::AnimNotify_NextAttackNotify()
{
	//Attack 시 Truning 시기를 설정
	//TurningNotify = true;
	OnNextAttack.Broadcast();
}

void UMonsterAnimInstance::AnimNotify_EndNotify()
{
	//Attack 시 Truning End 시기를 설정
	UE_LOG(LogTemp, Warning, TEXT("END NOTIFY"));
	//OwningCharacter->bBeDamaged = false;
	TurningNotify = false;
}


FName UMonsterAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}

bool UMonsterAnimInstance::IsMontagePlaying()
{
	return Montage_IsPlaying(MonsterAnimation.AttackMontage);
}


int32 UMonsterAnimInstance::GetMaxCombo()
{
	return MonsterAnimation.AttackMontage->GetNumSections();
}

void UMonsterAnimInstance::SetAnimationProperty(FMonsterAnim MonsterAnimation_)
{
	MonsterAnimation = MonsterAnimation_;
}

