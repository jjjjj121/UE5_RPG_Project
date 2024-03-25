// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerCombatComponent.h"

#include "Math/RotationMatrix.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/HitResult.h"

#include "RPGGame/RPGGameCharacter.h"

UPlayerCombatComponent::UPlayerCombatComponent()
	:LimitDistance(1000.f)
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


}

void UPlayerCombatComponent::ActiveLockon()
{
	float Radius = 600.f;
	float DrawDebugDuration = 1.f;

	FVector TraceVec = OwningActor->GetActorForwardVector() * LimitDistance;

	FVector Center = OwningActor->GetActorLocation() + (TraceVec * 0.5f);
	FQuat Rotation = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();

	float HalfHeight = LimitDistance * 0.5f;


	if (OwningActor) {
		//DrawDebugSphere(GetWorld(), Center, Radius, 20, FColor::Red, false, DrawDebugDuration);
		//DrawDebugCapsule(GetWorld(), Center,HalfHeight, Radius, Rotation, FColor::Red, false, DrawDebugDuration);


		TArray<FOverlapResult> OverlapResults;

		//GetWorld()->OverlapMultiByChannel(OverlapResults, OwnerPlayer->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, CollisionShape, CQParams);

		FCollisionShape MySphere = FCollisionShape::MakeSphere(Radius);
		TArray<FHitResult> OutResults;

		EObjectTypeQuery NewObjectChannel = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1);
		GetWorld()->SweepMultiByChannel(OutResults, Center, Center, FQuat::Identity, ECollisionChannel::ECC_WorldStatic, MySphere);
		DrawDebugSphere(GetWorld(), Center, Radius, 20, FColor::Red, false, DrawDebugDuration);


		UE_LOG(LogTemp, Warning, TEXT("Hit Acotr Num : %d"), OutResults.Num());

		//FCollisionObjectQueryParams ObejctList;

		//TArray<TEnumAsByte<enum EObjectTypeQuery>> objectTypes;
		//EObjectTypeQuery NewObjectChannel = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1);
		//objectTypes.Add(NewObjectChannel);

		//TArray<AActor*> IgnoreActor;

		//UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Center, Center, Radius, objectTypes, false, IgnoreActor, EDrawDebugTrace::ForDuration, OutResults, true);

		//UE_LOG(LogTemp, Warning, TEXT("Hit Acotr Num : %d"), OutResults.Num());



		//for (FHitResult Result : OutResults) {
		//	if (Result.bBlockingHit) {
		//		UE_LOG(LogTemp, Warning, TEXT("HIT RESULT : Actor Name : %s"), *Result.GetActor()->GetActorNameOrLabel());
		//	}
		//}


		//for (FOverlapResult OverlapResult : OverlapResults)
		//{
		//	if (AActor* Target = OverlapResult.GetActor())
		//	{
		//		if (Target->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		//		{
		//			if (IInteractionInterface::Execute_IsAvailableInteraction(Target))
		//			{
		//				TargetActor = Target;
		//				IInteractionInterface::Execute_SetTouchActor(Target, OwnerPlayer.Get());

		//				return;
		//			}
		//		}
		//	}
		//}
	}
}


