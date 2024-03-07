// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGamePlayerController.h"
#include "UserMenu/AC_UserMenuComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Library/WidgetEnumLibrary.h"
#include "Library/WidgetStructLibrary.h"
#include "Library/RPGWidgetFunctionLibrary.h"

#include "RPGGameCharacter.h"
#include "RPGGameHUD.h"

ARPGGamePlayerController::ARPGGamePlayerController()
{
	EnhancedInputMapping();

	/*시작 위젯 추가*/
	BaseWidgetName.Add(EWidgetNames::PlayerHUD);
	BaseWidgetName.Add(EWidgetNames::Interaction);

	UserMenuComp = CreateDefaultSubobject<UAC_UserMenuComponent>(TEXT("UserMenu"));

	PrimaryActorTick.bCanEverTick = true;

	/*Attack Turn Curve*/
	const ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Data/Curve/AttackTurn_Curve.AttackTurn_Curve'"));
	if (Curve.Succeeded()) {
		FloatCurve = Curve.Object;
	}
}

void ARPGGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (FloatCurve != nullptr) {
		/*Callback*/
		FOnTimelineFloat CurveCallback;
		FOnTimelineEvent LerpTimelineFinishedCallback;

		/*Bind Callback*/
		CurveCallback.BindUFunction(this, FName{ TEXT("OnTimelineUpdate") });
		LerpTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("OnTimelineFinished") });

		Timeline.AddInterpFloat(FloatCurve, CurveCallback);
		Timeline.SetTimelineFinishedFunc(LerpTimelineFinishedCallback);

		float TimelineLength = 0.1f;
		Timeline.SetTimelineLength(TimelineLength);

		//Timeline.PlayFromStart();
	}
}

void ARPGGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
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
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ARPGGamePlayerController::OnInteractPress);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ARPGGamePlayerController::OnInteractTrigger);

		//Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ARPGGamePlayerController::OnInventory);

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
		URPGWidgetFunctionLibrary::PushWidget(GetWorld(), WidgetName, EWidgetLayoutType::Main, EWidgetAnchorType::Fill);
	}
}

void ARPGGamePlayerController::OnInteractPress(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("[RPGGamePlayerController] : OnInteractPress"));

	FWidgetParam Widgetparam;
	Widgetparam.ActorParam = PossessedPlayer;

	URPGWidgetFunctionLibrary::ExecuteWidgetSingle(GetWorld(), EWidgetNames::Interaction, EWidgetFunctionNames::Interaction_PreesKey, Widgetparam);

}

void ARPGGamePlayerController::OnInteractTrigger(const FInputActionValue& Value)
{
	if (Value.Get<float>()) {
		//UE_LOG(LogTemp, Warning, TEXT("[RPGGamePlayerController] : OnInteractTrigger %f"), Value.Get<float>());
		FWidgetParam Widgetparam;
		Widgetparam.FloatParam = GetWorld()->GetDeltaSeconds();
		Widgetparam.ActorParam = PossessedPlayer;

		URPGWidgetFunctionLibrary::ExecuteWidgetSingle(GetWorld(), EWidgetNames::Interaction, EWidgetFunctionNames::Interaction_TriggerKey, Widgetparam);
	}

}

void ARPGGamePlayerController::OnInventory(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("[RPGGamePlayerController] : OnInventory"));

	if (Value.Get<bool>()) {
		UserMenuComp->ShowUserMenu(EUserMenuType::Inventory);
	}
}

void ARPGGamePlayerController::OnAttack(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("[RPGGamePlayerController] : OnAttack"));

	if (PossessedPlayer) {
		/*Attack*/
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
			FWidgetParam WidgetParam;
			Value.Get<float>() >= 1.f ? WidgetParam.BoolParam = true : WidgetParam.BoolParam = false;
			
			URPGWidgetFunctionLibrary::ExecuteWidgetSingle(GetWorld(), EWidgetNames::Interaction, EWidgetFunctionNames::Interaction_SelectRoot, WidgetParam);

			//if (Value.Get<float>() >= 1.f) {
			//	UE_LOG(LogTemp, Warning, TEXT("LIST UP"));

			//}
			//else if (Value.Get<float>() <= -1.f) {
			//	UE_LOG(LogTemp, Warning, TEXT("LIST Down"));
			//}
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

void ARPGGamePlayerController::OnTimelineUpdate()
{
	//UE_LOG(LogTemp, Warning, TEXT("[ARPGGamePlayerController] : Curve Update"));
	RotateCameraFront();
}

void ARPGGamePlayerController::OnTimelineFinished()
{
	//UE_LOG(LogTemp, Warning, TEXT("[ARPGGamePlayerController] : Timeline Finished"));
	CameraRotation = FRotator::ZeroRotator;
}

void ARPGGamePlayerController::RotateCameraFront()
{

	if (PossessedPlayer == nullptr || PlayerCameraManager == nullptr) {
		return;
	}

	FRotator CharacterRotation = FRotator::ZeroRotator;
	CharacterRotation.Yaw = PossessedPlayer->GetActorRotation().Yaw;

	/*첫 Attack 클릭 시에 바라보고 있는 방향으로만 설정되도록 함*/
	if (CameraRotation == FRotator::ZeroRotator) {
		CameraRotation.Yaw = PlayerCameraManager->GetCameraRotation().Yaw;
	}

	float Delta = GetWorld()->GetDeltaSeconds();

	//UE_LOG(LogTemp, Warning, TEXT("Delta Second : %f"), Delta);
	
	FRotator NewRotation = FMath::RInterpTo(CharacterRotation, CameraRotation, Delta, 8.f);
	PossessedPlayer->SetActorRotation(NewRotation);
}

void ARPGGamePlayerController::StartTurnTiemline()
{
	/*Rotate Camera front*/
	Timeline.PlayFromStart();
}
