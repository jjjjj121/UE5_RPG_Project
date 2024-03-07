// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/RPGCharacterMovementComponent.h"

#include "GameFramework/Character.h"

#include "Components/CapsuleComponent.h"

URPGCharacterMovementComponent::URPGCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GroundDistance = 0.f;
}

float URPGCharacterMovementComponent::GetGroundDistance()
{
	if (!CharacterOwner) {
		return 0.f;
	}

	/*Trace쏴서 Distance 계산*/

	if (MovementMode == MOVE_Walking)
	{
		GroundHitResult = CurrentFloor.HitResult;
		GroundDistance = 0.0f;
	}
	else {
		const UCapsuleComponent* CapsuleComp = CharacterOwner->GetCapsuleComponent();
		check(CapsuleComp);

		const float CapsuleHalfHeight = CapsuleComp->GetUnscaledCapsuleHalfHeight();
		
		/*UpdatedComponent == 제어중인 컴포넌트로 디폴트값은 RootComponent*/
		const ECollisionChannel CollisionChannel = (UpdatedComponent ? UpdatedComponent->GetCollisionObjectType() : ECC_Pawn);
		const FVector TraceStart(GetActorLocation());

		float GroundTraceDistance = 100000.0f;
		const FVector TraceEnd(TraceStart.X, TraceStart.Y, (TraceStart.Z - GroundTraceDistance - CapsuleHalfHeight));

		FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(URPGCharacterMovementComponent_CalculateGroundDistance), false, CharacterOwner);
		FCollisionResponseParams ResponseParam;
		InitCollisionParams(QueryParams, ResponseParam);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, CollisionChannel, QueryParams, ResponseParam);

		GroundHitResult = HitResult;
		GroundDistance = GroundTraceDistance;

		if (MovementMode == MOVE_NavWalking)
		{
			GroundDistance = 0.0f;
		}
		else if (HitResult.bBlockingHit)
		{
			GroundDistance = FMath::Max((HitResult.Distance - CapsuleHalfHeight), 0.0f);
		}
	}


	return GroundDistance;
}
