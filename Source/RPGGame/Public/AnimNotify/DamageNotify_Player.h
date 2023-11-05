// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DamageNotify_Player.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UDamageNotify_Player : public UAnimNotifyState
{
	GENERATED_BODY()
	
private:
	TArray<FHitResult> HitResults;

public:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

	TArray<AActor*> actorToIgnore;

	UPROPERTY(EditAnywhere)
		FName StartSocketName;

	UPROPERTY(EditAnywhere)
		FName EndSocketName;

	/*If it is true, damage check is performed through Tick*/
	UPROPERTY(EditAnywhere)
		bool EnableTickNotify;

	/*If it is true, damage check is performed only on EndNotify*/
	UPROPERTY(EditAnywhere)
		bool EnableOnceNotify;

	UPROPERTY(EditAnywhere)
		float DamageRadius = 15.f;

	UPROPERTY(EditAnywhere)
		float DamageScale = 1.0f;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UDamageType> DamageType;


	mutable FCriticalSection DataGaurd;
};
