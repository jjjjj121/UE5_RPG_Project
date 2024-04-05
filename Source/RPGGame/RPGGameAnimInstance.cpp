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
{
	static ConstructorHelpers::FObjectFinder<UDataAsset>DataAsset(TEXT("/Game/DataAsset/DA_Default_BehaviorAnim.DA_Default_BehaviorAnim"));

	if (DataAsset.Succeeded()) {
		DefaultAnimData = Cast<UBehaviorAnimData>(DataAsset.Object);
	}
	//UDataAsset* DataAsset;
	

}
void URPGGameAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningCharacter) {
		URPGCharacterMovementComponent* CharacterMovementComp = CastChecked<URPGCharacterMovementComponent>(OwningCharacter->GetCharacterMovement());
		GroundDistance = CharacterMovementComp->GetGroundDistance();
		//IsFight = OwningCharacter->IsFight;

		IsGuard = OwningCharacter->GetCombatComponent()->GetIsGuard();
	}



}

void URPGGameAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	UE_LOG(LogTemp, Warning, TEXT("NativeInitializeAnimation"));

	OwningCharacter = Cast<ARPGGameCharacter>(GetOwningActor());

}


void URPGGameAnimInstance::UpdateWeaponShield()
{
	/*bool Update*/
	if (ARPGGamePlayerController* Controller = Cast<ARPGGamePlayerController>(OwningCharacter->GetController())) {
		bEquipWeapon = Controller->UserMenuComp->IsEquipWeapon();
		bEquipShield = Controller->UserMenuComp->IsEquipShield();
	}

	///*Anim Update*/
	//if (bEquipWeapon) {
	//	if (UPlayerCombatComponent* CombatComponent = OwningCharacter->FindComponentByClass<UPlayerCombatComponent>()) {
	//		SetWeaponAnimData(CombatComponent->GetWeaponAnimData());
	//	}
	//}
	//if (bEquipShield) {
	//	if (UPlayerCombatComponent* CombatComponent = OwningCharacter->FindComponentByClass<UPlayerCombatComponent>()) {
	//		SetSheildAnimData(CombatComponent->GetShieldAnimData());
	//	}
	//}

	this->WeaponEnum = OwningCharacter->WeaponEnum;

}



void URPGGameAnimInstance::SetWeaponAnimData(UBehaviorAnimData* NewAnimData)
{
	WeaponAnimData = NewAnimData;
}

void URPGGameAnimInstance::SetSheildAnimData(UBehaviorAnimData* NewAnimData)
{
	ShieldAnimData = NewAnimData;
}

UBehaviorAnimData* URPGGameAnimInstance::GetCurBehavior()
{
	return bEquipWeapon ? WeaponAnimData : DefaultAnimData;
}


#pragma region Attack

void URPGGameAnimInstance::PlayAttackMontage()
{
	if (UBehaviorAnimData* CurBehavior = GetCurBehavior()) {
		FAnimDataArray AttackMontage = CurBehavior->GetMontageList(EMontageCategory::Attack);
		if (UAnimMontage* Montage = Cast<UAnimMontage>(AttackMontage.AnimAssetList[0])) {
			Montage_Play(Montage, 1.0f);
		}
	}

}

void URPGGameAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	if (UBehaviorAnimData* CurBehavior = GetCurBehavior()) {
		FAnimDataArray AttackMontage = CurBehavior->GetMontageList(EMontageCategory::Attack);
		if (UAnimMontage* Montage = Cast<UAnimMontage>(AttackMontage.AnimAssetList[0])) {
			Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), Montage);
		}
	}

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
	UBehaviorAnimData* CurBehavior;
	bEquipWeapon ? CurBehavior = WeaponAnimData : CurBehavior = DefaultAnimData;

	return FName(*FString::Printf(TEXT("Attack%d"), Section));
	//return AttackBehavior->GetAttackMontageSectionName(Section);
}


int32 URPGGameAnimInstance::GetMaxCombo()
{
	if (UBehaviorAnimData* CurBehavior = GetCurBehavior()) {
		FAnimDataArray AttackMontage = CurBehavior->GetMontageList(EMontageCategory::Attack);
		if (UAnimMontage* Montage = Cast<UAnimMontage>(AttackMontage.AnimAssetList[0])) {
			return Montage->GetNumSections();
		}
	}

	return 1;
}


#pragma endregion 


#pragma region Locomotion

UAnimationAsset* URPGGameAnimInstance::GetAnimAsset(UBehaviorAnimData* BehaviorAnimData, ELocomotionCategory LocomotionType, int32 Index)
{
	if (BehaviorAnimData == nullptr) {
		return nullptr;
	}

	if (FAnimDataArray* AnimDataArray = BehaviorAnimData->Locomotion->LocomotionAnimList.Find(LocomotionType)) {
		if (AnimDataArray->AnimAssetList.IsValidIndex(Index)) {
			return AnimDataArray->AnimAssetList[Index];
		}
	}

	return nullptr;
}


#pragma region

