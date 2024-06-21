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

void ARPGGameCharacter::SetAnimData(TSubclassOf<UAnimInstance> NewAnimLayer, FAnimMontageSet NewMontageSet)
{
	TSubclassOf<UAnimInstance> AnimLayer = NewAnimLayer != nullptr ? NewAnimLayer : DefaultAnimLayer;
	FAnimMontageSet MontageSet = NewMontageSet.LightAttackAnim != nullptr ? NewMontageSet : DefaultAnimMontageSet;

	GetMesh()->LinkAnimClassLayers(AnimLayer);

	CombatComponent->SetWeaponMontageset(MontageSet);

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
	//GetMesh()->LinkAnimClassLayers(DefaultAnimLayer);


	AnimInstance->OnEndRoll.AddLambda([this]()->void {
		if (URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(GetMovementComponent())) {
			MovementComp->bJumpable = true;
			PlayerState = EPlayerStateType::Locomotion;
			AnimInstance->StateType = EPlayerMovementType::Normal;

			//if (CombatComponent->GetLockedOn()) {
			//	CombatComponent->ActivateLockon();
			//}


			UE_LOG(LogTemp, Warning, TEXT("[AnimNotify_EndRoll]"));
		}
		});

	SetAnimData(nullptr, FAnimMontageSet());

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
		MyPlayerState->UpdateHP(Damage);

		if (MyPlayerState->State.CurHP <= 0) {
			IsDead = true;
		}
	}

	/*Direction Calculate*/
	FRotator Delta_A = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), DamageCauser->GetActorLocation());
	FRotator Delta_B = GetActorRotation();
	FRotator Delta_Rotator = UKismetMathLibrary::NormalizedDeltaRotator(Delta_A, Delta_B);

	FName Direction_Index = ConvertDirection(Delta_Rotator.Yaw);

	if (!IsDead) {

		// If you need the DamageType object like in blueprint, this is how you do it:
		UDamageType const* const DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();

		/*Check Damage Type*/
		const UDamageType_Base* MyDamageType = Cast<UDamageType_Base>(DamageTypeCDO);
		UAnimMontage* HitReact_Montage = nullptr;
		if (MyDamageType) {
			/*Damage Type : Charged Attack*/

			switch (MyDamageType->DamageType)
			{
			case EDamageType::Light:
				HitReact_Montage = DefaultAnimMontageSet.AdditiveHitReact;
				break;
			case EDamageType::Normal:
				HitReact_Montage = DefaultAnimMontageSet.AdditiveHitReact;	//TEST
				//HitReact_Montage = DefaultAnimMontageSet.NormalHitReact;
				break;
			case EDamageType::Heavy:
				HitReact_Montage = DefaultAnimMontageSet.HeavyHitReact;
				break;
			default:
				break;
			}
		}

		AnimInstance->Montage_Play(HitReact_Montage);
		AnimInstance->Montage_JumpToSection(Direction_Index, HitReact_Montage);

		ReceivingDamage(MyPlayerState->State.MaxHP, MyPlayerState->State.CurHP);
	}
	/*Player Dead*/
	else {
		DoDeath(Direction_Index);
	}



	return Damage;
}

void ARPGGameCharacter::Attack(bool IsPressed)
{
	CombatComponent->Attack(IsPressed);
}

void ARPGGameCharacter::Charging()
{
	CombatComponent->Charging();
}


FName ARPGGameCharacter::ConvertDirection(float Direction)
{
	/*Hit Front*/
	if (Direction >= -45.f && Direction <= 45.f) {
		return FName(TEXT("Fwd"));
	}
	/*Hit Back*/
	else if ((Direction >= -180.f && Direction < -135.f) || (Direction >= 135.f && Direction < 180.f)) {
		return FName(TEXT("Bwd"));
	}
	/*Hit Right*/
	else if (Direction > 45.f && Direction <= 135.f) {
		return FName(TEXT("Right"));
	}
	/*Hit Left*/
	else if (Direction >= -135.f && Direction < -45.f) {
		return FName(TEXT("Left"));
	}

	/*Error*/
	return FName();
}

void ARPGGameCharacter::DoDeath(FName DirectionIndex)
{
	if (UAnimMontage* DeathReact_Montage = DeathReact.FindRef(DirectionIndex)) {
		//UE_LOG(LogTemp, Warning, TEXT("[ARPGGameCharacter::DoDeath] : DirectionIndex _ %s"), *DirectionIndex.ToString());

		AnimInstance->Montage_Play(DeathReact_Montage);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		/*TEST*/
		
		IsDead = true;

	}
}

float ARPGGameCharacter::GetDamage()
{
	ARPGGamePlayerState* MyPlayerState = Cast<ARPGGamePlayerState>(GetPlayerState());
	if (MyPlayerState) {
		return MyPlayerState->State.Damage;
	}

	return -1.f;
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

		//Roll
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnRoll);

		//Equip
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnEquip);

		//Sprint
		EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnGuard);

		//Lockon
		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::OnLockOn);
	}

}

void ARPGGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	//InputVector = Value.Get<FVector2D>();

	/*Calculate Local InputVec*/
	FRotator ControlRotation = FRotator::ZeroRotator;
	ControlRotation.Yaw = GetControlRotation().Yaw;

	FVector ForwardVec = UKismetMathLibrary::GetForwardVector(ControlRotation);
	FVector RightVec = UKismetMathLibrary::GetRightVector(ControlRotation);

	FVector InputVec = (ForwardVec * MovementVector.Y) + (RightVec * MovementVector.X);
	FVector NewVec = GetActorTransform().InverseTransformVectorNoScale(InputVec);

	LocalInputVector.X = NewVec.Y;
	LocalInputVector.Y = NewVec.X;

	//float Degree = UKismetMathLibrary::DegAtan2(LocalInputVector.Y, LocalInputVector.X);

	//UE_LOG(LogTemp, Warning, TEXT("[ARPGGameCharacter::Move] : Degree _ %f"), Degree);


	if (Controller != nullptr) {
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


void ARPGGameCharacter::OnWalk(const FInputActionValue& Value)
{
	if (URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(GetCharacterMovement())) {

		/*예외 처리*/
		if (CombatComponent->GetIsGuard() || MovementComp->IsFalling()) {
			return;
		}



		if (MovementComp->PlayerState != EPlayerMovementType::Walk) {
			MovementComp->MaxWalkSpeed = 200.f;
			//MovementType = EPlayerMovementType::Walk;
			MovementComp->PlayerState = EPlayerMovementType::Walk;
		}
		else {
			MovementComp->MaxWalkSpeed = 400.f;
			//MovementType = EPlayerMovementType::Normal;
			MovementComp->PlayerState = EPlayerMovementType::Normal;
		}

	}

}

void ARPGGameCharacter::OnSprint(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("VALUE : %f"), Value.Get<float>());

	if (URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(GetCharacterMovement())) {

		/*예외 처리*/
		if (CombatComponent->GetIsGuard() || MovementComp->IsFalling()) {
			return;
		}


		if (Value.Get<float>() > 0.f) {
			MovementComp->MaxWalkSpeed = 600.f;
			MovementComp->PlayerState = EPlayerMovementType::Sprint;
			//MovementType = EPlayerMovementType::Sprint;


		}
		else {
			MovementComp->MaxWalkSpeed = 400.f;
			MovementComp->PlayerState = EPlayerMovementType::Normal;
			//MovementType = EPlayerMovementType::Normal;
		}

	}

}

void ARPGGameCharacter::OnRoll(const FInputActionValue& Value)
{
	if (!AnimInstance->IsAnyMontagePlaying()) {
		URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(GetMovementComponent());
		if (!MovementComp->IsFalling()) {
			UAnimMontage* PlayMontage;


			//MovementComp->bOrientRotationToMovement = true;
			//bUseControllerRotationYaw = false;

			/*Roll ? Dodge*/
			if (GetVelocity().Length() > 0) {
				PlayMontage = DefaultAnimMontageSet.RollAnim;
				MovementComp->PlayerState = EPlayerMovementType::Roll;

				AnimInstance->InputVector = LocalInputVector;

				///*TEST*/
				//if(CombatComponent->GetLockedOn()){
				//	FVector CurAcceleration = MovementComp->GetCurrentAcceleration();
				//	FVector Velocity = GetVelocity();

				//	FVector AccelerationDirection = UKismetMathLibrary::Divide_VectorFloat(CurAcceleration - Velocity, GetWorld()->GetDeltaSeconds());
				//	FRotator NewRotation = UKismetMathLibrary::Conv_VectorToRotator(AccelerationDirection);

				//	SetActorRotation(NewRotation);
				//	APlayerController* PlayerController = Cast<APlayerController>(Controller);

				//	//DisableInput(PlayerController);
				//}
				//
				//AnimInstance->PlayMontage(PlayMontage);
				AnimInstance->StateType = EPlayerMovementType::Roll;

				//AnimInstance->Montage_JumpToSection(ConvertDirection(AnimInstance->CurrentDirection), PlayMontage);
			}
			else {
				PlayMontage = DefaultAnimMontageSet.DodgeAnim;
				MovementComp->PlayerState = EPlayerMovementType::Dodge;
				//AnimInstance->StateType = EPlayerMovementType::Dodge;

				//AnimInstance->PlayMontage(PlayMontage);
			}



			MovementComp->bJumpable = false;
		}
	}



}

void ARPGGameCharacter::OnEquip(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnEquip"));
	
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
	//UE_LOG(LogTemp, Warning, TEXT("[ARPGGameCharacter::OnLockOn] : Press Key"));
	if (!IsDead) {
		CombatComponent->GetLockedOn() ? CombatComponent->DeactivateLockon() : CombatComponent->ActivateLockon();
	}
}

void ARPGGameCharacter::OnJump()
{
	if (!IsDead) {
		URPGCharacterMovementComponent* MovementComp = CastChecked<URPGCharacterMovementComponent>(GetMovementComponent());
		if (MovementComp->bJumpable && !AnimInstance->IsAnyMontagePlaying()) {
			Jump();
		}
	}

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

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Roll(TEXT("/Game/ThirdPerson/Input/Actions/IA_Roll.IA_Roll"));
	if (IA_Roll.Succeeded()) {
		RollAction = IA_Roll.Object;
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

