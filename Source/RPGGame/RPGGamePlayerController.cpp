// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGamePlayerController.h"
#include "Inventory/AC_InventoryComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Library/WidgetEnumLibrary.h"
#include "Library/RPGWidgetFunctionLibrary.h"

#include "RPGGameCharacter.h"
#include "RPGGameHUD.h"

ARPGGamePlayerController::ARPGGamePlayerController()
{
	EnhancedInputMapping();

	/*시작 위젯 추가*/
	BaseWidgetName.Add(EWidgetNames::PlayerHUD);

	Inventory = CreateDefaultSubobject<UAC_InventoryComponent>(TEXT("INVENTORY"));
}

void ARPGGamePlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	PossessedPlayer = Cast<ARPGGameCharacter>(NewPawn);
	HUD = Cast<ARPGGameHUD>(GetHUD());

	SetupInput();
	SetupWidget();

}

void ARPGGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	BindAction();
}

void ARPGGamePlayerController::BindAction()
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ARPGGamePlayerController::OnInteract);

		//Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ARPGGamePlayerController::OnInventory);
		UE_LOG(LogTemp, Warning, TEXT("BindAction : CONTROLLER"));

		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ARPGGamePlayerController::OnAttack);

		//List Up Down
		EnhancedInputComponent->BindAction(ListUpDownAction, ETriggerEvent::Started, this, &ARPGGamePlayerController::OnWheelUpDown);
	}
}

void ARPGGamePlayerController::SetupInput()
{
	if (PossessedPlayer)
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			subsystem->AddMappingContext(InputMappingContext, 1);
		}
	}
}

void ARPGGamePlayerController::SetupWidget()
{
	for (const FName& WidgetName : BaseWidgetName) {
		URPGWidgetFunctionLibrary::PushWidget(GetWorld(), WidgetName, EWidgetLayoutType::Main);
	}
}

void ARPGGamePlayerController::OnInteract(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("[RPGGamePlayerController] : OnInteract"));

	//if (Value.Get<bool>()) {
	//	if (HUD->bRootItem) {
	//		HUD->OpenRootItemList();
	//	}
	//}
}

void ARPGGamePlayerController::OnInventory(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("[RPGGamePlayerController] : OnInventory"));

	if (Value.Get<bool>()) {
		Inventory->ShowInventory();
	}
}

void ARPGGamePlayerController::OnAttack(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("[RPGGamePlayerController] : OnAttack"));

	if (PossessedPlayer) {
		PossessedPlayer->Attack();
	}
}

void ARPGGamePlayerController::OnWheelUpDown(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("[RPGGamePlayerController] : OnWheelUpDown"));

	if (Value.Get<bool>()) {
		if (WheelType == EWheelType::Default) {
			UE_LOG(LogTemp, Warning, TEXT("EWheelType : Default"));
		}
		else if (WheelType == EWheelType::ListType) {
			if (Value.Get<float>() >= 1.f) {
				UE_LOG(LogTemp, Warning, TEXT("LIST UP"));
			}
			else if (Value.Get<float>() <= -1.f) {
				UE_LOG(LogTemp, Warning, TEXT("LIST Down"));
			}
		}
	}

}


void ARPGGamePlayerController::EnhancedInputMapping()
{
	/*맵핑 설정 추가*/
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Interaction(TEXT("/Game/ThirdPerson/Input/Actions/IA_Interaction.IA_Interaction"));
	if (IA_Interaction.Succeeded()) {
		InteractAction = IA_Interaction.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Inventory(TEXT("/Game/ThirdPerson/Input/Actions/IA_Inventory.IA_Inventory"));
	if (IA_Inventory.Succeeded()) {
		InventoryAction = IA_Inventory.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Attack(TEXT("/Game/ThirdPerson/Input/Actions/IA_Attack.IA_Attack"));
	if (IA_Attack.Succeeded()) {
		AttackAction = IA_Attack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_WheelUpDown(TEXT("/Game/ThirdPerson/Input/Actions/IA_WheelUpDown.IA_WheelUpDown"));
	if (IA_WheelUpDown.Succeeded()) {
		ListUpDownAction = IA_WheelUpDown.Object;
	}


}