// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/InteractionComponent.h"

#include "RPGGame/RPGGameCharacter.h"
#include "Interface/InteractionInterface.h"

#include "Library/WidgetEnumLibrary.h"
#include "Library/WidgetStructLibrary.h"
#include "Library/RPGWidgetFunctionLibrary.h"

#include "Monster/Monster_AI.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SensingRadius = 100.f;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<ARPGGameCharacter>(GetOwner());

	// Overlap Settings
	CollisionShape = FCollisionShape::MakeSphere(SensingRadius);

	CQParams.AddIgnoredActor(GetOwner());
	CQParams.bTraceComplex = false;
	CQParams.TraceTag = TEXT("Interaction");
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateSensing();
	UpdateUI();
}

void UInteractionComponent::UpdateSensing()
{
	TArray<FOverlapResult> OverlapResults;
	GetWorld()->OverlapMultiByChannel(OverlapResults, OwnerPlayer->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, CollisionShape, CQParams);

	for (FOverlapResult OverlapResult : OverlapResults)
	{
		if (AActor* Target = OverlapResult.GetActor())
		{
			if (Target->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			{
				if (IInteractionInterface::Execute_IsAvailableInteraction(Target))
				{
					TargetActor = Target;
					IInteractionInterface::Execute_SetTouchActor(Target, OwnerPlayer.Get());

					return;
				}
			}
		}
	}

	TargetActor = nullptr;
}

void UInteractionComponent::UpdateUI()
{
	FWidgetParam WidgetParam;

	if (TargetActor.IsValid()) {

		WidgetParam.BoolParam = true;
		WidgetParam.ActorParam = TargetActor.Get();
		WidgetParam.NameParam = IInteractionInterface::Execute_GetInteractionActorName(TargetActor.Get());
		WidgetParam.VectorParam = IInteractionInterface::Execute_GetInteractionWidgetLocation(TargetActor.Get());
	}

	URPGWidgetFunctionLibrary::ExecuteWidgetSingle(GetWorld(), EWidgetNames::Interaction, EWidgetFunctionNames::Interaction, WidgetParam);

}

bool UInteractionComponent::CanInteraction() const
{
	return TargetActor.IsValid();
}

bool UInteractionComponent::ExecuteInteraction(UItemInstance* NewItemInstance)
{
	if (TargetActor.IsValid() == false) {
		return 0;
	}

	if (NewItemInstance == nullptr) {
		return 0;
	}

	return IInteractionInterface::Execute_ExecuteInteraction(TargetActor.Get(), GetOwner(), NewItemInstance);
}

void UInteractionComponent::StopInteraction()
{
	if (TargetActor.IsValid() == false) {
		return;
	}

	IInteractionInterface::Execute_StopInteration(TargetActor.Get(), GetOwner());
}

