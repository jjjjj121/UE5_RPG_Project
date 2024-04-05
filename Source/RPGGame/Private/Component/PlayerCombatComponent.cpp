// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerCombatComponent.h"

#include "RPGGame/RPGGameAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"

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
}



void UPlayerCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("COMBAT COMP : TICK COMPONENT"));

	if (bIsLockedOn) {
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwningActor->GetActorLocation(), Target->GetActorLocation());
		OwningActor->GetController()->SetControlRotation(LookAtRotation);

		float Distance = (Target->GetActorLocation() - OwningActor->GetActorLocation()).Length();

		if (Distance > LimitUnLockDistance) {
			DeactivateLockon();
		}
	}


}

#pragma region Guard
void UPlayerCombatComponent::ActivateGuard()
{
	OwningActor->GetCharacterMovement()->MaxWalkSpeed = 200.f;
	bIsGuard = true;

}

void UPlayerCombatComponent::DeactivateGuard()
{

	OwningActor->GetCharacterMovement()->MaxWalkSpeed = 400.f;
	bIsGuard = false;

}

#pragma endregion

#pragma region LockOn
void UPlayerCombatComponent::ActivateLockon()
{

	if (OwningActor) {

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

