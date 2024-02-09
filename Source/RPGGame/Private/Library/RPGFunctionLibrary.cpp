// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/RPGFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "RPGGame/RPGGameCharacter.h"
#include "RPGGame/RPGGamePlayerController.h"
#include "RPGGame/RPGGamePlayerState.h"

#include "System/RPGGameInstance.h"

#include "UserMenu/Inventory/ItemActor.h"

ARPGGameCharacter* URPGFunctionLibrary::GetPlayerCharacter(const UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr)
		return nullptr;

	return Cast<ARPGGameCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0));
}

ARPGGamePlayerController* URPGFunctionLibrary::GetPlayerController(const UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr)
		return nullptr;

	return Cast<ARPGGamePlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}

ARPGGamePlayerState* URPGFunctionLibrary::GetPlayerState(const UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr) 
		return nullptr;

	return Cast<ARPGGamePlayerState>(UGameplayStatics::GetPlayerState(WorldContextObject, 0));
}

URPGGameInstance* URPGFunctionLibrary::GetBOTWGameInstance(const UObject* WorldContextObject)
{
	if (WorldContextObject == nullptr)
		return nullptr;

	return Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
}

AItemActor* URPGFunctionLibrary::SpawnItemtoPlayer(const UObject* WorldContextObject, FString ItemID, FName AttachSocket)
{
	if (WorldContextObject == nullptr)
		return nullptr;

	FTransform Transform = GetPlayerCharacter(WorldContextObject)->GetActorTransform();
	
	FVector NewLocation = Transform.GetLocation() + GetPlayerCharacter(WorldContextObject)->GetActorForwardVector()*100.f;
	Transform.SetLocation(NewLocation);

	//FTransform Transform = AttachSocket.IsNone() ? GetPlayerCharacter(WorldContextObject)->GetActorTransform() : GetPlayerCharacter(WorldContextObject)->GetMesh()->GetSocketTransform(AttachSocket);

	AItemActor* NewItem = Cast<AItemActor>(WorldContextObject->GetWorld()->SpawnActorDeferred<AActor>(AItemActor::StaticClass(), Transform));
	NewItem->ItemID = ItemID;

	NewItem->FinishSpawning(Transform);

	return NewItem;
}
