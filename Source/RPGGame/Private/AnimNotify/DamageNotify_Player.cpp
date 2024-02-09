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


				if (Controller->UserMenuComp->IsEquipWeapon()) {

					UE_LOG(LogTemp, Warning, TEXT("[UDamageNotify_Player] : EQUIP WEAPON"));
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("[UDamageNotify_Player] : NOT EQUIP WEAPON"));
				}




				FVector StartPosition = MeshComp->GetSocketLocation(StartSocketName);
				FVector EndPosition = MeshComp->GetSocketLocation(EndSocketName);

				ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2);
				float Damage = Player->GetDamage() * DamageScale;

				bool Result = UKismetSystemLibrary::SphereTraceMulti(MeshComp, StartPosition, EndPosition, DamageRadius, MyTraceType, false, actorToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FColor::Red, FColor::Green, 1.f);


				if (Result) {
					for (FHitResult HitResult : HitResults) {
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

	if (EnableOnceNotify) {
		ARPGGameCharacter* Player = Cast<ARPGGameCharacter>(MeshComp->GetOwner());
		if (Player) {
			FVector StartPosition = MeshComp->GetSocketLocation(StartSocketName);
			FVector EndPosition = MeshComp->GetSocketLocation(EndSocketName);

			ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel2);

			float Damage = Player->GetDamage() * DamageScale;

			bool Result = UKismetSystemLibrary::SphereTraceMulti(MeshComp, StartPosition, EndPosition, DamageRadius, MyTraceType, false, actorToIgnore, EDrawDebugTrace::ForDuration, HitResults, true, FColor::Red, FColor::Green, 1.f);

			if (Result) {
				for (FHitResult HitResult : HitResults) {
					actorToIgnore.Add(HitResult.GetActor());
					if (HitResult.GetActor()->ActorHasTag("Monster")) {
						UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, Player->GetController(), Player, DamageType ? DamageType : NULL);
					}
				}
			}
		}
	}
}
