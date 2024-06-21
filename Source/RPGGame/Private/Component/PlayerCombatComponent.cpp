// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerCombatComponent.h"
#include "Component/RPGCharacterMovementComponent.h"

#include "RPGGame/RPGGameAnimInstance.h"
#include "RPGGame/RPGGamePlayerController.h"

//#include "GameFramework/CharacterMovementComponent.h"

#include "Math/RotationMatrix.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/HitResult.h"


#include "RPGGame/RPGGameCharacter.h"

UPlayerCombatComponent::UPlayerCombatComponent()
	:LimitLockOnDistance(1000.f)
	, LimitUnLockDistance(1200.f)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningActor = Cast<ARPGGameCharacter>(GetOwner());

	/*Anim Instance Init*/
	AnimInstance = Cast<URPGGameAnimInstance>(OwningActor->GetMesh()->GetAnimInstance());

	//AnimInstance->OnMontageEnded.AddDynamic(this, &UPlayerCombatComponent::OnAttackMontageEnded);

	//Init Attack Combo
	AttackEndComboState();

	AnimInstance->OnChargeAttack.AddLambda([this]()->void {
		bFullCharged = true;
		IsComboInputOn = true;

		});

	AnimInstance->OnNextAttack.AddLambda([this]()->void {

		if (IsComboInputOn) {
			OnNextAttack();
		}
		else {
			CanNextCombo = true;
		}

		});
}

void UPlayerCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("COMBAT COMP : TICK COMPONENT"));

	/*Lock On*/
	if (bIsLockedOn) {
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwningActor->GetActorLocation(), Target->GetActorLocation());
		OwningActor->GetController()->SetControlRotation(LookAtRotation);

		float Distance = (Target->GetActorLocation() - OwningActor->GetActorLocation()).Length();

		if (Distance > LimitUnLockDistance) {
			DeactivateLockon();
		}
	}

	/*Jump Attack Land*/
	if (AnimInstance->Montage_IsPlaying(WeaponMontageset.JumpAttackAnim) && AnimInstance->bLandable) {

		if (bDoOnce) {
			AnimInstance->Montage_JumpToSection(EAnimSectionName::Land, WeaponMontageset.JumpAttackAnim);
			bDoOnce = false;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("[UPlayerCombatComponent::ActivateGuard] : bISGuard : %d"), bIsGuard);

	//float AnimCurve = FMath::Abs((AnimInstance->GetCurveValue(FName("GroundDistance"))));
	//UE_LOG(LogTemp, Warning, TEXT("GROUND DISTANCE Anim Curve : %f"), AnimCurve);

	//float Distance =AnimInstance->GetGroundDistance();
	//UE_LOG(LogTemp, Warning, TEXT("GROUND DISTANCE : %f"), Distance);
}

void UPlayerCombatComponent::PlayMontageWithBind(UAnimMontage* NewMontage)
{
	AnimInstance->PlayMontage(NewMontage);

	if (URPGCharacterMovementComponent* CharacterMovementComp = CastChecked<URPGCharacterMovementComponent>(OwningActor->GetCharacterMovement())) {
		CharacterMovementComp->bJumpable = false;
	}


	if (AnimInstance->OnMontageEnded.IsBound()) {
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &UPlayerCombatComponent::OnAttackMontageEnded);
	}

	AnimInstance->OnMontageEnded.AddDynamic(this, &UPlayerCombatComponent::OnAttackMontageEnded);

}


#pragma region Attack

void UPlayerCombatComponent::Charging()
{
	IsComboInputOn = false;
	CanNextCombo = true;
	PlayMontageWithBind(WeaponMontageset.ChargeAttackAnim);

}

void UPlayerCombatComponent::ChargingAttack()
{
	AttackStartComboState();

	FString SectionStr = EAnimSectionName::Attack.ToString();
	FString ComboStr = FString::Printf(TEXT("%d"), CurrentCombo);
	SectionStr.Append(ComboStr);

	FName CurSectionName = AnimInstance->Montage_GetCurrentSection();
	FName NextSectionName = FName(*SectionStr);

	//AnimInstance->Montage_SetNextSection(CurSectionName, NextSectionName, WeaponMontageset.ChargeAttackAnim);
	AnimInstance->Montage_JumpToSection(NextSectionName, WeaponMontageset.ChargeAttackAnim);
}

void UPlayerCombatComponent::LightAttack()
{
	PlayMontageWithBind(WeaponMontageset.LightAttackAnim);
	AttackStartComboState();

	FName CurSectionName = AnimInstance->Montage_GetCurrentSection();
	FName NextSectionName = AnimInstance->GetMontageNextSectionName(EAnimSectionName::Attack, CurrentCombo);

	AnimInstance->Montage_JumpToSection(NextSectionName, WeaponMontageset.LightAttackAnim);

	//AnimInstance->Montage_SetNextSection(CurSectionName, NextSectionName, WeaponMontageset.ChargeAttackAnim);
}

void UPlayerCombatComponent::MeleeJumpAttack()
{
	if (URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(OwningActor->GetMovementComponent())) {

		if (MovementComp->GetGroundDistance() > 100.f) {
			UE_LOG(LogTemp, Warning, TEXT("[UPlayerCombatComponent::MeleeJumpAttack] : Ground DIstance _ %f"), MovementComp->GetGroundDistance());

			PlayMontageWithBind(WeaponMontageset.JumpAttackAnim);
			AttackStartComboState();

			FName NextSectionName = AnimInstance->GetMontageNextSectionName(EAnimSectionName::Attack, CurrentCombo);
			AnimInstance->Montage_JumpToSection(NextSectionName, WeaponMontageset.JumpAttackAnim);

			FName CurSectionName = AnimInstance->Montage_GetCurrentSection();
			AnimInstance->Montage_SetNextSection(CurSectionName, EAnimSectionName::Loop, WeaponMontageset.JumpAttackAnim);

			AnimInstance->bLandable = true;

			AnimInstance->OnMontageEnded.AddDynamic(this, &UPlayerCombatComponent::JumpAttackMontageEnded);
		}
	}
}

void UPlayerCombatComponent::DodgeAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("[UPlayerCombatComponent::DodgeAttack]"));

	if (URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(OwningActor->GetMovementComponent())) {

		PlayMontageWithBind(WeaponMontageset.DodgeAttackAnim);
		AttackStartComboState();

		FName CurSectionName = AnimInstance->Montage_GetCurrentSection();
		FName NextSectionName = AnimInstance->GetMontageNextSectionName(EAnimSectionName::Attack, CurrentCombo);

		AnimInstance->Montage_JumpToSection(NextSectionName, WeaponMontageset.DodgeAttackAnim);

		MovementComp->PlayerState = EPlayerMovementType::Normal;
	}

}

void UPlayerCombatComponent::RollAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("[UPlayerCombatComponent::RollAttack]"));

	if (URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(OwningActor->GetMovementComponent())) {

		PlayMontageWithBind(WeaponMontageset.RollAttackAnim);
		AttackStartComboState();

		FName CurSectionName = AnimInstance->Montage_GetCurrentSection();
		FName NextSectionName = AnimInstance->GetMontageNextSectionName(EAnimSectionName::Attack, CurrentCombo);

		AnimInstance->Montage_JumpToSection(NextSectionName, WeaponMontageset.DodgeAttackAnim);

		MovementComp->PlayerState = EPlayerMovementType::Normal;
	}
}


void UPlayerCombatComponent::Attack(bool IsPressed)
{
	/*First Attack*/
	if (URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(OwningActor->GetMovementComponent())) {
		if (CurrentCombo <= 0) {
			if (IsPressed) {
				switch (MovementComp->PlayerState)
				{
				case EPlayerMovementType::Dodge:
					IsComboInputOn = true;
					break;
				case EPlayerMovementType::Roll:
					IsComboInputOn = true;
					break;
				case EPlayerMovementType::Fall:
					MeleeJumpAttack();
					break;

				default:
					UE_LOG(LogTemp, Warning, TEXT("[UPlayerCombatComponent::Attack] : Default"));
					Charging();
					break;
				}

			}
			else {
				if (CanNextCombo) {
					IsComboInputOn = true;
					OnNextAttack();
				}
			}
		}
		else {
			if (IsPressed) {
				IsComboInputOn = true;
				if (CanNextCombo) {
					//UE_LOG(LogTemp, Warning, TEXT("[UPlayerCombatComponent: Attack] : CanNextCombo"));
					OnNextAttack();
				}

			}
		}

	}

}

void UPlayerCombatComponent::OnNextAttack()
{
	//UE_LOG(LogTemp, Warning, TEXT("[UPlayerCombatComponent] : OnNextAttack  _ %d"), IsComboInputOn);
	if (URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(OwningActor->GetMovementComponent())) {
		if (IsComboInputOn) {
			if (bFullCharged) {
				ChargingAttack();
			}
			else {
				switch (MovementComp->PlayerState)
				{
				case EPlayerMovementType::Dodge:
					DodgeAttack();
					break;
				case EPlayerMovementType::Roll:
					RollAttack();
					break;
				default:
					LightAttack();
					break;
				}
			}
		}
	}

	TurnAttack();

	IsComboInputOn = false;

}

void UPlayerCombatComponent::TurnAttack()
{
	if (ARPGGamePlayerController* PlayerController = Cast<ARPGGamePlayerController>(OwningActor->Controller)) {
		PlayerController->StartTurnTiemline();
	}
}

void UPlayerCombatComponent::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

	/*정상 완료된 경우 == 애니메이션이 끝남.*/
	if (!bInterrupted) {
		bFullCharged = false;
		IsAttacking = false;

		AttackEndComboState();
		//UE_LOG(LogTemp, Warning, TEXT("[UPlayerCombatComponent::OnAttackMontageEnded]"));

		if (URPGCharacterMovementComponent* CharacterMovementComp = CastChecked<URPGCharacterMovementComponent>(OwningActor->GetCharacterMovement())) {
			CharacterMovementComp->bJumpable = true;
			CharacterMovementComp->PlayerState = EPlayerMovementType::Normal;

		}

	}
	/*중단된 경우 == 다른 애니메이션으로 교체된 경우(Attack Combo)*/
	else {
		//UE_LOG(LogTemp, Warning, TEXT("UPlayerCombatComponent::OnAttackMontageEnded : bInterrupted true"));
	}

}

void UPlayerCombatComponent::JumpAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bDoOnce = true;

	AnimInstance->OnMontageEnded.RemoveDynamic(this, &UPlayerCombatComponent::JumpAttackMontageEnded);
}

void UPlayerCombatComponent::AttackStartComboState()
{
	CanNextCombo = false;
	IsComboInputOn = false;

	IsAttacking = true;
	AnimInstance->SetIsFight(true);

	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, GetMaxCombo());

}

void UPlayerCombatComponent::AttackEndComboState()
{
	CanNextCombo = false;
	IsComboInputOn = false;
	CurrentCombo = 0;
}

int32 UPlayerCombatComponent::GetMaxCombo()
{
	if (UAnimMontage* CurMontage = AnimInstance->GetCurrentActiveMontage()) {
		return CurMontage->GetNumSections();
	}

	return 0;
}

#pragma endregion

#pragma region Guard
void UPlayerCombatComponent::ActivateGuard()
{

	if (URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(OwningActor->GetCharacterMovement())) {

		/*예외 처리*/
		if (IsAttacking || MovementComp->IsFalling()) {
			DeactivateGuard();
			return;
		}

		MovementComp->PlayerState = EPlayerMovementType::Walk;
		bIsGuard = true;

	}

}

void UPlayerCombatComponent::DeactivateGuard()
{

	if (URPGCharacterMovementComponent* CharacterMovementComp = CastChecked<URPGCharacterMovementComponent>(OwningActor->GetCharacterMovement())) {
		CharacterMovementComp->PlayerState = EPlayerMovementType::Normal;
		bIsGuard = false;
	}

}

#pragma endregion

#pragma region LockOn
void UPlayerCombatComponent::ActivateLockon()
{

	if (OwningActor) {

		if (Target == nullptr) {

			FVector Center = OwningActor->GetActorLocation();

			TArray<FHitResult> OutResults;

			TArray<TEnumAsByte<enum EObjectTypeQuery>> objectTypes;
			EObjectTypeQuery NewObjectChannel = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1);
			objectTypes.Add(NewObjectChannel);

			TArray<AActor*> IgnoreActor;

			UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Center, Center, LimitLockOnDistance, objectTypes, false, IgnoreActor, EDrawDebugTrace::ForDuration, OutResults, true);

			float NearestDistance = 0;

			for (FHitResult Result : OutResults) {
				if (Result.bBlockingHit) {
					FVector PlayerLoc = OwningActor->GetActorForwardVector();
					FVector PlayerLoc2 = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorForwardVector();
					FVector TargetLoc = (Result.GetActor()->GetActorLocation() - OwningActor->GetActorLocation()).GetSafeNormal();

					float Dot = FVector::DotProduct(PlayerLoc2, TargetLoc);

					if (Dot > 0.5f) {

						float NewDistance = (Result.GetActor()->GetActorLocation() - OwningActor->GetActorLocation()).Length();
						//UE_LOG(LogTemp, Warning, TEXT("HIT RESULT : Actor Name : %s , NewDistance : %f"), *Result.GetActor()->GetActorNameOrLabel(), NewDistance);

						if (!NearestDistance || NewDistance < NearestDistance) {
							Target = Result.GetActor();
						}

					}
				}
			}
		}
		

		if (Target != nullptr) {
			OwningActor->GetCharacterMovement()->bOrientRotationToMovement = false;
			OwningActor->bUseControllerRotationYaw = true;
			OwningActor->GetAnimInstance()->SetIsFight(true);


			bIsLockedOn = true;
		}

	}
}

void UPlayerCombatComponent::DeactivateLockon()
{
	UE_LOG(LogTemp, Warning, TEXT("UPlayerCombatComponent::DeactivateLockon"));


	OwningActor->GetCharacterMovement()->bOrientRotationToMovement = true;
	OwningActor->bUseControllerRotationYaw = false;
	OwningActor->GetAnimInstance()->SetIsFight(false);

	bIsLockedOn = false;
	Target = nullptr;


}

#pragma endregion

