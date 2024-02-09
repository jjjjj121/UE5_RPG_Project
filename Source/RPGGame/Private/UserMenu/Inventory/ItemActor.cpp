// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMenu/Inventory/ItemActor.h"

#include "Library/RPGFunctionLibrary.h"

#include "UserMenu/AC_UserMenuComponent.h"
#include "UserMenu/Inventory/ItemDefinition.h"

#include "Components/SphereComponent.h"

#include "RPGGame/RPGGameCharacter.h"
#include "RPGGame/RPGGamePlayerController.h"


// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ITEMMESH"));
	InteractColl = CreateDefaultSubobject<USphereComponent>(TEXT("INTERACTCOLL"));

	RootComponent = ItemMeshComp;
	InteractColl->SetupAttachment(ItemMeshComp);

	InteractColl->SetSphereRadius(150.0f);
	InteractColl->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnOverlapBegin);
	InteractColl->OnComponentEndOverlap.AddDynamic(this, &AItemActor::OnOverlapEnd);

	ItemMeshComp->SetSimulatePhysics(true);
	InteractColl->SetCollisionProfileName(FName("Interaction"));
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	ItemInstance = NewObject<UItemInstance>(this);
	//ItemInstance->ItemDefinition = NewObject<UItemDefinition>(this);
	ItemInstance->InitInstance(ItemID);

	FItemData ItemData = ItemInstance->ItemDefinition->GetItemData();

	/*Set Mesh*/
	if (UStaticMesh* NewMesh = ItemData.ItemMesh) {
		ItemMeshComp->SetStaticMesh(NewMesh);
	}

}

void AItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AItemActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AItemActor::IsAvailableInteraction_Implementation() const
{
	return true;
}

bool AItemActor::ExecuteInteraction_Implementation(AActor* InteractionTarget, UItemInstance* NewItemInstance)
{
	UE_LOG(LogTemp, Warning, TEXT("[AItemActor] : ExecuteInteraction_Implementation"));

	// TouchActor의 인벤토리에 추가
	if (ACharacter* Character = Cast<ACharacter>(TouchActor))
	{
		if (ARPGGamePlayerController* PlayerController = URPGFunctionLibrary::GetPlayerController(Character))
		{
			if (UAC_UserMenuComponent* InventoryComponent = PlayerController->FindComponentByClass<UAC_UserMenuComponent>())
			{

				if (InventoryComponent->AddItemToInventory(ItemInstance))
				{
					Destroy();
					return true;
				}
			}
		}
	}

	return false;
}

void AItemActor::StopInteration_Implementation(AActor* InteractionTarget)
{
}

void AItemActor::SetTouchActor_Implementation(AActor* NewTouchActor)
{
	TouchActor = Cast<ARPGGameCharacter>(NewTouchActor);
}

TArray<UItemInstance*> AItemActor::GetRootItemList_Implementation()
{
	TArray<UItemInstance*> RootItems;
	RootItems.Add(ItemInstance);

	return RootItems;
}

FName AItemActor::GetInteractionActorName_Implementation()
{
	//UItemDefinition* ItemDef = Cast<UItemDefinition>(ItemInstance->ItemDefinition->GetDefaultObject());
	FItemData ItemData = ItemInstance->ItemDefinition->GetItemData();

	return FName(ItemData.ItemName);
}

FVector AItemActor::GetInteractionWidgetLocation_Implementation()
{
	FVector WidgetLocation = GetActorLocation();
	WidgetLocation.Z += 30.f;

	return WidgetLocation;
}

