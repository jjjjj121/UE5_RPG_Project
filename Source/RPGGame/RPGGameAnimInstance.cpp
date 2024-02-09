// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/Vector.h"

#include "RPGGameCharacter.h"
#include "RPGGamePlayerController.h"
#include "UserMenu/AC_UserMenuComponent.h"

#include "DataAsset/LocomotionData.h"
#include "DataAsset/BehaviorAnimData.h"

#include "Behavior/AttackBehavior.h"
#include "Behavior/AttackBehavior_Non.h"

#include "Kismet/KismetMathLibrary.h"

URPGGameAnimInstance::URPGGameAnimInstance(FObjectInitializer const& object_initializer) : Super(object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UDataAsset>DataAsset(TEXT("/Game/DataAsset/DA_Default_Locomotion_Player.DA_Default_Locomotion_Player"));

	if (DataAsset.Succeeded()) {
		DefaultLocomotion = Cast<ULocomotionData>(DataAsset.Object);
	}
	//UDataAsset* DataAsset;


}
void URPGGameAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningCharacter) {
		UpdateAnimProperty();
		UpdateIsPawnFalling();
		UpdateWeapon();
		UpdateYawPitch();
	}
	
}

void URPGGameAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	UE_LOG(LogTemp, Warning, TEXT("NativeInitializeAnimation"));

	OwningCharacter = Cast<ARPGGameCharacter>(GetOwningActor());
	if(OwningCharacter){
		MovementComponent = OwningCharacter->GetCharacterMovement();

		FRotator Delta_A = OwningCharacter->GetControlRotation();
		FRotator Delta_B = OwningCharacter->GetActorRotation();
		FRotator Delta_Rotator = UKismetMathLibrary::NormalizedDeltaRotator(Delta_A, Delta_B);

		PitchAnim = Delta_Rotator.Pitch;
		YawAnim = Delta_Rotator.Yaw;
	}

	SetBehavior(UAttackBehavior_Non::StaticClass());
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
	if (ARPGGamePlayerController* Controller = Cast<ARPGGamePlayerController>(OwningCharacter->GetController())) {
		//UE_LOG(LogTemp, Warning, TEXT("URPGGameAnimInstance : UpdateWeapon"));
		bEquipWeapon = Controller->UserMenuComp->IsEquipWeapon();
	}

	this->WeaponEnum = OwningCharacter->WeaponEnum;

}

void URPGGameAnimInstance::UpdateYawPitch()
{

	FRotator Delta_A = OwningCharacter->GetControlRotation();
	FRotator Delta_B = OwningCharacter->GetActorRotation();
	FRotator Target_Rotator = UKismetMathLibrary::NormalizedDeltaRotator(Delta_A, Delta_B);

	FRotator Cur_Rotator = UKismetMathLibrary::MakeRotator(0.f, YawAnim, PitchAnim);

	FRotator Result_Rotator = FMath::RInterpTo(Cur_Rotator, Target_Rotator, 1.f, 0.0f);

	PitchAnim = Result_Rotator.Pitch;
	YawAnim = Result_Rotator.Yaw;

}


#pragma region Attack

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
	if (AttackBehavior) {
		auto asd = AttackBehavior->MaxCombo;
		UE_LOG(LogTemp, Warning, TEXT("BEHAVIOR SUCCEED"));
	}
	AttackBehavior->ParentAnimInstance = this;

}

#pragma endregion 


#pragma region Locomotion

UAnimationAsset* URPGGameAnimInstance::GetAnimAsset(ULocomotionData* LocomotionData, ELocomotion LocomotionType, int32 Index)
{
	if (LocomotionData == nullptr) {
		return nullptr;
	}

	if (FAnimDataArray* AnimDataArray = LocomotionData->LocomotionData.Find(LocomotionType)) {
		if (AnimDataArray->AnimAssetList.IsValidIndex(Index)) {
			return AnimDataArray->AnimAssetList[Index];
		}
	}


	return nullptr;
}

#pragma region

