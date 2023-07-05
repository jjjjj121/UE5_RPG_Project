// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/Vector.h"
#include "RPGGameCharacter.h"
#include "Actor/Item/AttackBehavior.h"
#include "Actor/Item/AttackBehavior_Non.h"

URPGGameAnimInstance::URPGGameAnimInstance()
{

	SetBehavior(UAttackBehavior_Non::StaticClass());

} 

void URPGGameAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningCharacter) {
		UpdateAnimProperty();
		UpdateIsPawnFalling();
		UpdateWeapon();
	}
}

void URPGGameAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	UE_LOG(LogTemp, Warning, TEXT("NativeInitializeAnimation"));

	OwningCharacter = Cast<ARPGGameCharacter>(GetOwningActor());
	if(OwningCharacter){
		MovementComponent = OwningCharacter->GetCharacterMovement();
	}
}


void URPGGameAnimInstance::UpdateAnimProperty()
{
	//set velocity & direction
	Velocity = MovementComponent->Velocity;
	CurDirection= CalculateDirection(MovementComponent->Velocity, OwningCharacter->GetActorRotation());

	//2D Size == vector length XY
	CurrentPawnSpeed = Velocity.Size2D();

	FVector Acceleration = MovementComponent->GetCurrentAcceleration();
	if (Acceleration != FVector(0.0f, 0.0f, 0.0f) && CurrentPawnSpeed > 3.0f) {
		ShouldMove = true;
	}
	else {
		ShouldMove = false;
	}
}

void URPGGameAnimInstance::UpdateIsPawnFalling()
{
	IsFaliing = MovementComponent->IsFalling();
}

void URPGGameAnimInstance::UpdateWeapon()
{
	this->WeaponEnum = OwningCharacter->WeaponEnum;

}

void URPGGameAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackBehavior->AttackMontage, 1.0f);

}

void URPGGameAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), AttackBehavior->AttackMontage);
}

void URPGGameAnimInstance::AnimNotify_AttackHitNotify()
{
	//해당 델리게이트 안에 있는 모든 함수 실행
	OnAttackHit.Broadcast();
}

void URPGGameAnimInstance::AnimNotify_NextAttackNotify()
{
	OnNextAttack.Broadcast();
}


FName URPGGameAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return AttackBehavior->GetAttackMontageSectionName(Section);
}


int32 URPGGameAnimInstance::GetMaxCombo()
{
	return AttackBehavior->MaxCombo;
}

void URPGGameAnimInstance::SetBehavior(TSubclassOf<UAttackBehavior> Behavior)
{
	AttackBehavior = NewObject<UAttackBehavior>(this, Behavior, FName(TEXT("Behavior")));

	AttackBehavior->ParentAnimInstance = this;

}