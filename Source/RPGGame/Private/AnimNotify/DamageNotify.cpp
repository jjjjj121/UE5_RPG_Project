// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/DamageNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Monster/Monster_AI.h"
#include "Kismet/GameplayStatics.h"
#include "Monster/MonsterAnimInstance.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


void UDamageNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	actorToIgnore.Empty();
}

void UDamageNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	if (EnableTickNotify) {
		AMonster_AI* OwnerMonster = Cast<AMonster_AI>(MeshComp->GetOwner());

		if (OwnerMonster) {
			FVector StartPosition = MeshComp->GetSocketLocation(StartSocketName);
			FVector EndPosition = MeshComp->GetSocketLocation(EndSocketName);

			ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2);
			float Damage = OwnerMonster->Damage * DamageScale;

			bool Result = UKismetSystemLibrary::SphereTraceMulti(MeshComp, StartPosition, EndPosition, DamageRadius, MyTraceType, false, actorToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FColor::Red, FColor::Green, 1.f);

			if (Result) {
				for (FHitResult HitResult : HitResults) {
					actorToIgnore.Add(HitResult.GetActor());
					if (HitResult.GetActor()->ActorHasTag("Player")) {
						UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, OwnerMonster->GetController(), OwnerMonster, DamageType ? DamageType : NULL);

					}
				}
			}
		}
	}
}

void UDamageNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	actorToIgnore.Empty();

	AMonster_AI* OwnerMonster = Cast<AMonster_AI>(MeshComp->GetOwner());

	if (EnableOnceNotify) {
		if (OwnerMonster) {
			FVector StartPosition = MeshComp->GetSocketLocation(StartSocketName);
			FVector EndPosition = MeshComp->GetSocketLocation(EndSocketName);

			ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2);
			float Damage = OwnerMonster->Damage * DamageScale;

			bool Result = UKismetSystemLibrary::SphereTraceMulti(MeshComp, StartPosition, EndPosition, DamageRadius, MyTraceType, false, actorToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FColor::Red, FColor::Green, 1.f);

			if (Result) {
				for (FHitResult HitResult : HitResults) {
					actorToIgnore.Add(HitResult.GetActor());
					if (HitResult.GetActor()->ActorHasTag("Player")) {
						UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, OwnerMonster->GetController(), OwnerMonster, DamageType ? DamageType : NULL);

					}
				}
			}
		}
	}

	//OwnerMonster->MonsterAnimInstance->OnNextAttack.Broadcast();
}
