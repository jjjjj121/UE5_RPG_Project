// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "RPGGameAnimInstance.h"
#include "Actor/Item/EquipItem.h"


//////////////////////////////////////////////////////////////////////////
// ARPGGameCharacter

ARPGGameCharacter::ARPGGameCharacter()
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

	/*맵핑 설정 추가*/
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Interaction(TEXT("/Game/ThirdPerson/Input/Actions/IA_Interaction.IA_Interaction"));
	if (IA_Interaction.Succeeded()) {
		InteractAction = IA_Interaction.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Inventory(TEXT("/Game/ThirdPerson/Input/Actions/IA_Inventory.IA_Inventory"));
	if (IA_Interaction.Succeeded()) {
		InventoryAction = IA_Inventory.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_Attack(TEXT("/Game/ThirdPerson/Input/Actions/IA_Attack.IA_Attack"));
	if (IA_Attack.Succeeded()) {
		AttackAction = IA_Attack.Object;
	}

	AttackEndComboState();
}

void ARPGGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	/*Anim Instance Init*/
	AnimInstance = Cast<URPGGameAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &ARPGGameCharacter::OnAttackMontageEnded);

	//OnNextAttack 델리게이트에 람다 함수식 추가 -> Broadcast시 호출
	AnimInstance->OnNextAttack.AddLambda([this]()->void {
		CanNextCombo = false;
		if (IsComboInputOn) {
			AttackStartComboState();
			AnimInstance->JumpToAttackMontageSection(CurrentCombo);	//다음 콤보 Montage로 switching
			UE_LOG(LogTemp, Warning, TEXT("Attack Combo : %d"), CurrentCombo);
		}
		});

}

void ARPGGameCharacter::Attack()
{
	//공격 중인경우
	if (IsAttacking) {
		//다음 콤보가 있는 경우
		if (CanNextCombo) {
			IsComboInputOn = true;
			UE_LOG(LogTemp, Warning, TEXT("IsComboInputOn"));
		}
	}
	//첫 Attack 콤보인 경우
	else {
		AttackStartComboState();
		AnimInstance->PlayAttackMontage();	//Montage 실행
		IsAttacking = true;
	}
}

bool ARPGGameCharacter::GetIsAttacking()
{
	return IsAttacking;
}


void ARPGGameCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	AttackEndComboState();
}

void ARPGGameCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARPGGameCharacter::Look);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ARPGGameCharacter::OnInteract);

		//Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ARPGGameCharacter::OnInventory);

		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ARPGGameCharacter::OnAttack);
	}

}

void ARPGGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
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

void ARPGGameCharacter::OnInteract(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact In"));
	if (Value.Get<bool>()) {
		UE_LOG(LogTemp, Warning, TEXT("Interact On"));
	}
	
}

void ARPGGameCharacter::OnInventory(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory In"));
	if (Value.Get<bool>()) {
		UE_LOG(LogTemp, Warning, TEXT("Inventory On"));
	}
}

void ARPGGameCharacter::OnAttack(const FInputActionValue& Value)
{
	this->Attack();
}


void ARPGGameCharacter::EquipWeapon()
{
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters SpawnPrams;
		SpawnPrams.Owner = this;

		FRotator rotator;
		FVector spawnlocation = GetMesh()->GetSocketLocation(FName(TEXT("Weapon")));
		
		Weapon = Cast<AEquipItem>(world->SpawnActor<AActor>(AEquipItem::StaticClass(), spawnlocation, rotator, SpawnPrams));

		

	}
	//AnimInstance->SetBehavior();
}

