// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/DamageNotify_Player.h"

#include "RPGGame/RPGGameCharacter.h"
#include "RPGGame/RPGGamePlayerController.h"

#include "UserMenu/AC_UserMenuComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UDamageNotify_Player::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	actorToIgnore.Empty();

}

void UDamageNotify_Player::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	if (EnableTickNotify) {
		if (ARPGGameCharacter* Player = Cast<ARPGGameCharacter>(MeshComp->GetOwner())) {
			if (ARPGGamePlayerController* Controller = Cast<ARPGGamePlayerController>(Player->GetOwner())) {

				FVector StartPosition = MeshComp->GetSocketLocation(StartSocketName);
				FVector EndPosition = MeshComp->GetSocketLocation(EndSocketName);

				ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2);
				float Damage = Player->GetDamage() * DamageScale;
				bool Result = UKismetSystemLibrary::SphereTraceMulti(MeshComp, StartPosition, EndPosition, DamageRadius, MyTraceType, false, actorToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FColor::Red, FColor::Green, 5.f);

				if (HitResults.Num()) {
					UE_LOG(LogTemp, Warning, TEXT("HitResult : %d"), HitResults.Num());
					for (FHitResult HitResult : HitResults) {
						if (actorToIgnore.Contains(HitResult.GetActor())) {
							//UE_LOG(LogTemp, Warning, TEXT("[UDamageNotify::NotifyTick] : Already Apply Damage"));
							break;
						}
						actorToIgnore.Add(HitResult.GetActor());

						if (HitResult.GetActor()->ActorHasTag("Monster")) {
							UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, Player->GetController(), Player, DamageType ? DamageType : NULL);
						}

					}
				}


			}
		}
	}
}

void UDamageNotify_Player::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	actorToIgnore.Empty();

	if (!EnableTickNotify) {
		ARPGGameCharacter* Player = Cast<ARPGGameCharacter>(MeshComp->GetOwner());
		if (Player) {
			FVector StartPosition = MeshComp->GetSocketLocation(StartSocketName);
			FVector EndPosition = MeshComp->GetSocketLocation(EndSocketName);

			ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2);

			float Damage = Player->GetDamage() * DamageScale;

			bool Result = UKismetSystemLibrary::SphereTraceMulti(MeshComp, StartPosition, EndPosition, DamageRadius, MyTraceType, false, actorToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FColor::Red, FColor::Green, 1.f);

			if (Result) {
				for (FHitResult HitResult : HitResults) {
					if (actorToIgnore.Contains(HitResult.GetActor())) {
						//UE_LOG(LogTemp, Warning, TEXT("[UDamageNotify::NotifyTick] : Already Apply Damage"));
						break;
					}
					actorToIgnore.Add(HitResult.GetActor());
					if (HitResult.GetActor()->ActorHasTag("Monster")) {
						UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, Player->GetController(), Player, DamageType ? DamageType : NULL);
					}
				}
			}
		}
	}
}
