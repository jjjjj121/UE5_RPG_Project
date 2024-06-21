// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/Vector.h"

#include "RPGGameCharacter.h"
#include "RPGGamePlayerController.h"

#include "UserMenu/AC_UserMenuComponent.h"
#include "Component/PlayerCombatComponent.h"
#include "Component/RPGCharacterMovementComponent.h"

#include "DataAsset/LocomotionData.h"
#include "DataAsset/BehaviorAnimData.h"

#include "Kismet/KismetMathLibrary.h"

URPGGameAnimInstance::URPGGameAnimInstance(FObjectInitializer const& object_initializer) : Super(object_initializer)
, LandableDistance(100.f)
{


}
void URPGGameAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningCharacter) {
		GroundDistance = MovementComponent->GetGroundDistance();

		IsGuard = OwningCharacter->GetCombatComponent()->GetIsGuard();

		UpdateLandalbe();
	}

}


void URPGGameAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<ARPGGameCharacter>(GetOwningActor());

	if (OwningCharacter) {
		MovementComponent = Cast<URPGCharacterMovementComponent>(OwningCharacter->GetCharacterMovement());
	}


}

void URPGGameAnimInstance::PlayMontage(UAnimMontage* NewMontage , float Newrate)
{
	Montage_Play(NewMontage, Newrate);
}

void URPGGameAnimInstance::PlayMontage_Section(UAnimMontage* NewMontage, FName NewSectionName)
{

	Montage_SetNextSection(NewSectionName, Montage_GetCurrentSection(), NewMontage);
}


#pragma region Attack

void URPGGameAnimInstance::AnimNotify_AttackHitNotify()
{
	//해당 델리게이트 안에 있는 모든 함수 실행
	OnAttackHit.Broadcast();
}

void URPGGameAnimInstance::AnimNotify_NextAttackNotify()
{
	OnNextAttack.Broadcast();
}

void URPGGameAnimInstance::AnimNotify_ChargeAttackNotify()
{
	//UE_LOG(LogTemp, Warning, TEXT("Charge Notify"));
	OnChargeAttack.Broadcast();
}

void URPGGameAnimInstance::AnimNotify_EndRoll()
{
	//UE_LOG(LogTemp, Warning, TEXT("[AnimNotify_EndRoll]"));
	//MovementComponent->bJumpable = true;


	
	OnEndRoll.Broadcast();
}

FName URPGGameAnimInstance::GetMontageNextSectionName(FName SectionName, int32 SectionNum)
{
	FString SectionStr = SectionName.ToString();
	FString ComboStr = FString::Printf(TEXT("%d"), SectionNum);
	SectionStr.Append(ComboStr);

	FName CurSectionName = Montage_GetCurrentSection();
	FName NextSectionName = FName(*SectionStr);

	return NextSectionName;
}

void URPGGameAnimInstance::UpdateLandalbe()
{
	if (MovementComponent->IsFalling() && GroundDistance <= LandableDistance) {
		bLandable = true;
	}
	else {
		bLandable = false;
	}
}


#pragma endregion 



