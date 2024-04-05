// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGGameCharacter.h"
#include "GameFramework/Controller.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interface/InteractionComponent.h"
#include "Component/PlayerCombatComponent.h"
#include "Component/RPGCharacterMovementComponent.h"
#include "UserMenu/AC_UserMenuComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "RPGGameAnimInstance.h"
#include "RPGGame/RPGGamePlayerState.h"
#include "RPGGame/RPGGamePlayerController.h"
#include "RPGGame/RPGGameHUD.h"
#include "Engine/DamageEvents.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "DamageType/DamageType_Base.h"


//////////////////////////////////////////////////////////////////////////
// ARPGGameCharacter

void ARPGGameCharacter::SetAnimLayer(TSubclassOf<UAnimInstance> NewAnimLayer)
{
	TSubclassOf<UAnimInstance> AnimLayer = NewAnimLayer != nullptr ? NewAnimLayer : DefaultAnimLayer;
	GetMesh()->LinkAnimClassLayers(AnimLayer);
	
}

ARPGGameCharacter::ARPGGameCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<URPGCharacterMovementComponent>(CharacterMovementComponentName)),
	MovementType(EPlayerMovementType::Normal)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


	//Init Attack Combo
	AttackEndComboState();

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));

	CombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));
	
	/*Input Mapping*/
	EnhancedInputMapping();


}

void ARPGGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Player Tag 추가
	Tags.Add(FName(TEXT("Player")));

	//Add Input Mapping Context

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		//HUD
		HUD = Cast<ARPGGameHUD>(PlayerController->GetHUD());
	}

	/*Anim Instance Init*/
	AnimInstance = Cast<URPGGameAnimInstance>(GetMesh()->GetAnimInstance());
	GetMesh()->LinkAnimClassLayers(DefaultAnimLayer);


	AnimInstance->OnMontageEnded.AddDynamic(this, &ARPGGameCharacter::OnAttackMontageEnded);
	
	//OnNextAttack 델리게이트에 람다 함수식 추가 -> Broadcast시 호출
	AnimInstance->OnNextAttack.AddLambda([this]()->void {
		CanNextCombo = false;
		if (IsComboInputOn) {
			AttackStartComboState();
			AnimInstance->JumpToAttackMontageSection(CurrentCombo);	//다음 콤보 Montage로 switching
			TurnAttack();
			//UE_LOG(LogTemp, Warning, TEXT("Attack Combo : %d"), CurrentCombo);
		}
		});

}

void ARPGGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

float ARPGGameCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	UE_LOG(LogClass, Warning, TEXT("Damage : %f"), Damage);

	ARPGGamePlayerState* MyPlayerState = Cast<ARPGGamePlayerState>(GetPlayerState());
	if (MyPlayerState) {
		MyPlayerState->UpdateHP(-Damage);

		if (MyPlayerState->State.CurHP <= 0) {
			IsDead = true;
		}
	}

	FRotator Delta_A = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), DamageCauser->GetActorLocation());
	FRotator Delta_B = GetActorRotation();
	FRotator Delta_Rotator = UKismetMathLibrary::NormalizedDeltaRotator(Delta_A, Delta_B);

	int32 Direction_Index = CalculateDirectionIndex(Delta_Rotator.Yaw);

	if (!IsDead) {
		
		// If you need the DamageType object like in blueprint, this is how you do it:
		UDamageType const* const DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();

		/*Check Damage Type*/
		const UDamageType_Base* MyDamageType = Cast<UDamageType_Base>(DamageTypeCDO);
		UAnimMontage* HitReact_Montage = nullptr;
		if (MyDamageType) {
			/*Damage Type : Charged Attack*/
			if (MyDamageType->IsCharged) {
				HitReact_Montage = Charged_Hit_Reaction_Montages.FindRef(Direction_Index);
				//UE_LOG(LogTemp, Warning, TEXT("CHARGED"));
			}
			/*Damage Type : Basic Attack*/
			else {
				HitReact_Montage = Basic_Hit_Reaction_Montages.FindRef(Direction_Index);
				//UE_LOG(LogTemp, Warning, TEXT("BASIC"));
			}
		}
		
		AnimInstance->Montage_Play(HitReact_Montage);

		ReceivingDamage(MyPlayerState->State.MaxHP, MyPlayerState->State.CurHP);
	}
	/*Player Dead*/
	else {
		DoDeath(Direction_Index);
	}

	

	return Damage;
}

void ARPGGameCharacter::Attack()
{
	//공격 중인경우
	if (IsAttacking) {
		//다음 콤보가 있는 경우
		if (CanNextCombo) {
			IsComboInputOn = true;
		}
	}
	//첫 Attack 콤보인 경우
	else {
		UnCrouch();
		AttackStartComboState();
		AnimInstance->PlayAttackMontage();	//Montage 실행
		TurnAttack();
		IsAttacking = true;
	}
}

bool ARPGGameCharacter::GetIsAttacking()
{
	return IsAttacking;
}

int32 ARPGGameCharacter::CalculateDirectionIndex(float Direction)
{
	/*Hit Front*/
	if (Direction >= -45.f && Direction <= 45.f) {
		return 1;
	}
	/*Hit Right*/
	else if (Direction > 45.f && Direction <= 135.f) {
		return 2;
	}
	/*Hit Left*/
	else if (Direction >= -135.f && Direction < -45.f) {
		return 3;
	}
	/*Hit Back*/
	else if ((Direction >= -180.f && Direction < -135.f) || (Direction >= 135.f && Direction < 180.f)) {
		return 4;
	}

	/*Error*/
	return -1;
}

void ARPGGameCharacter::DoDeath(int32 DirectionIndex)
{
	AnimInstance->Montage_Play(Death_Reaction_Montages.FindRef(DirectionIndex));

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

float ARPGGameCharacter::GetDamage()
{
	ARPGGamePlayerState* MyPlayerState = Cast<ARPGGamePlayerState>(GetPlayerState());
	if (MyPlayerState) {
		return MyPlayerState->State.Damage;
	}
	
	return -1.f;
}

void ARPGGameCharacter::TurnAttack()
{
	if (ARPGGamePlayerController* PlayerController = Cast<ARPGGamePlayerController>(Controller)) {
		PlayerController->StartTurnTiemline();
	}
}

//void ARPGGameCharacter::SetFightStance(bool NewStance)
//{
//	IsFight = NewStance;
//
//	if (IsFight == true) {
//
//		UE_LOG(LogTemp, Warning, TEXT("On Fight Stance : Start"));
//
//		GetWorld()->GetTimerManager().SetTimer(
//			OnFightTimerHandle,
//			FTimerDelegate::CreateLambda([this]() {
//				UE_LOG(LogTemp, Warning, TEXT("On Fight Stance : Timer"));
//				IsFight = false;
//				}), 10.f, false);
//	}
//
//
//}

void ARPGGameCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	AttackEndComboState();
}

void ARPGGameCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	//SetFightStance(true);
	AnimInstance->SetIsFight(true);
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo +1, 1, AnimInstance->GetMaxCombo());


}

void ARPGGameCharacter::AttackEndComboState()
{
	CanNextCombo = false;
	IsComboInputOn = false;
	CurrentCombo = 0;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARPGGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::Look);

		//Crouching
		//EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ARPGGameCharacter::OnCrouch);

		//Walk
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnWalk);

		//Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnSprint);

		//Equip
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnEquip);

		//Sprint
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnGuard);

		//Equip
		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnLockOn);
	}

}

void ARPGGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr){
		if (ARPGGamePlayerState* MyPlayerState = Cast<ARPGGamePlayerState>(GetPlayerState())) {
			if (!IsDead) {
				// find out which way is forward
				const FRotator Rotation = Controller->GetControlRotation();
				const FRotator YawRotation(0, Rotation.Yaw, 0);

				// get forward vector
				const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

				// get right vector 
				const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

				// add movement 
				AddMovementInput(ForwardDirection, MovementVector.Y);
				AddMovementInput(RightDirection, MovementVector.X);
			}
		}
	}
}

void ARPGGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}



//void ARPGGameCharacter::OnCrouch(const FInputActionValue& Value)
//{
//	if (const URPGCharacterMovementComponent* MyMoveComp = CastChecked<URPGCharacterMovementComponent>(GetCharacterMovement())) {
//
//		if (bIsCrouched || MyMoveComp->bWantsToCrouch) {
//			UnCrouch();
//		}
//		else if (MyMoveComp->IsMovingOnGround()) {
//			Crouch();
//		}
//	}
//	//UE_LOG(LogTemp, Warning, TEXT("CROUCH"));
//}

void ARPGGameCharacter::OnWalk(const FInputActionValue& Value)
{
	if (URPGCharacterMovementComponent* MyMoveComp = CastChecked<URPGCharacterMovementComponent>(GetCharacterMovement())) {
		if (MovementType != EPlayerMovementType::Walk) {
			MyMoveComp->MaxWalkSpeed = 200.f;
			MovementType = EPlayerMovementType::Walk;
		}
		else {
			MyMoveComp->MaxWalkSpeed = 400.f;
			MovementType = EPlayerMovementType::Normal;
		}
	}

}

void ARPGGameCharacter::OnSprint(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("VALUE : %f"), Value.Get<float>());
	
	if (URPGCharacterMovementComponent* MyMoveComp = CastChecked<URPGCharacterMovementComponent>(GetCharacterMovement())) {
		if (Value.Get<float>() > 0.f) {
			MyMoveComp->MaxWalkSpeed = 600.f;
			MovementType = EPlayerMovementType::Sprint;
		}
		else {
			MyMoveComp->MaxWalkSpeed = 400.f;
			MovementType = EPlayerMovementType::Normal;
		}

	}

}

void ARPGGameCharacter::OnEquip(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("OnEquip"));

	if (ARPGGamePlayerController* PlayerController = Cast<ARPGGamePlayerController>(Controller)) {
		if (UAC_UserMenuComponent* UserMenuComponent = PlayerController->FindComponentByClass<UAC_UserMenuComponent>()) {
			UserMenuComponent->OnHandedWeapon();

		}
	}

}

void ARPGGameCharacter::OnGuard(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("[ARPGGameCharacter::OnGuard] : Press Key _ %f"), Value.Get<float>());
	if (Value.Get<float>() > 0.f) {
		CombatComponent->ActivateGuard();
	}
	else {
		CombatComponent->DeactivateGuard();
	}


}

void ARPGGameCharacter::OnLockOn(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("[ARPGGameCharacter::OnLockOn] : Press Key"));

	CombatComponent->GetLockedOn() ? CombatComponent->DeactivateLockon() : CombatComponent->ActivateLockon();

}

void ARPGGameCharacter::OnJump()
{
	UnCrouch();
	Jump();
}


void ARPGGameCharacter::EnhancedInputMapping()
{
	//static ConstructorHelpers::FObjectFinder<UInputAction>IA_Crouch(TEXT("/Game/ThirdPerson/Input/Actions/IA_Crouch.IA_Crouch"));
	//if (IA_Crouch.Succeeded()) {
	//	CrouchAction = IA_Crouch.Object;
	//}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Walk(TEXT("/Game/ThirdPerson/Input/Actions/IA_Walk.IA_Walk"));
	if (IA_Walk.Succeeded()) {
		WalkAction = IA_Walk.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Sprint(TEXT("/Game/ThirdPerson/Input/Actions/IA_Sprint.IA_Sprint"));
	if (IA_Sprint.Succeeded()) {
		SprintAction = IA_Sprint.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Equip(TEXT("/Game/ThirdPerson/Input/Actions/IA_Equip.IA_Equip"));
	if (IA_Equip.Succeeded()) {
		EquipAction = IA_Equip.Object;
	}


	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Guard(TEXT("/Game/ThirdPerson/Input/Actions/IA_Guard.IA_Guard"));
	if (IA_Guard.Succeeded()) {
		GuardAction = IA_Guard.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_LockOn(TEXT("/Game/ThirdPerson/Input/Actions/IA_LockOn.IA_LockOn"));
	if (IA_LockOn.Succeeded()) {
		LockOnAction = IA_LockOn.Object;
	}

}

void ARPGGameCharacter::EquipWeapon()
{
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters SpawnPrams;
		SpawnPrams.Owner = this;

		FRotator rotator;
		FVector spawnlocation = GetMesh()->GetSocketLocation(FName(TEXT("Weapon")));
		
		//웨폰 추가
		//Weapon = Cast<AEquipItem>(world->SpawnActor<AActor>(AEquipItem::StaticClass(), spawnlocation, rotator, SpawnPrams));

	}
	//AnimInstance->SetBehavior();
}

