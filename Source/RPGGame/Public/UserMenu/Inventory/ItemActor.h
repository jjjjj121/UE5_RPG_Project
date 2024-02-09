// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInstance.h"
#include "Interface/InteractionInterface.h"

#include "ItemActor.generated.h"

/*레벨에 배치되는 Item 엑터 클래스*/
UCLASS()
class RPGGAME_API AItemActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:
	AItemActor();

	UPROPERTY(EditAnywhere, Category = Info)
		UItemInstance* ItemInstance;
	UPROPERTY(EditAnywhere, Category = Info)
		FString ItemID;
	UPROPERTY(VisibleAnywhere, Category = Info)
		UStaticMeshComponent* ItemMeshComp;

	UPROPERTY(VisibleAnywhere, Category = Info)
		class USphereComponent* InteractColl;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	virtual void Tick(float DeltaTime) override;


	/*Interaction Interface*/
public:
	virtual bool IsAvailableInteraction_Implementation() const override;
	virtual bool ExecuteInteraction_Implementation(AActor* InteractionTarget, UItemInstance* NewItemInstance) override;
	virtual void StopInteration_Implementation(AActor* InteractionTarget) override;
	virtual void SetTouchActor_Implementation(AActor* NewTouchActor) override;
	virtual TArray<UItemInstance*> GetRootItemList_Implementation() override;
	virtual FName GetInteractionActorName_Implementation() override;
	virtual FVector GetInteractionWidgetLocation_Implementation() override;
};
