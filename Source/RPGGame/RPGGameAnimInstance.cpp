// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/Vector.h"
#include "RPGGameCharacter.h"

void URPGGameAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningCharacter) {
		UpdateAnimProperty();
		UpdateIsPawnFalling();
		UpdateWeapon();
	}
}

void URPGGameAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	UE_LOG(LogTemp, Warning, TEXT("NativeInitializeAnimation"));

	OwningCharacter = Cast<ARPGGameCharacter>(GetOwningActor());
	if(OwningCharacter){
		MovementComponent = OwningCharacter->GetCharacterMovement();
	}
}


void URPGGameAnimInstance::UpdateAnimProperty()
{
	//set velocity & direction
	Velocity = MovementComponent->Velocity;
	CurDirection= CalculateDirection(MovementComponent->Velocity, OwningCharacter->GetActorRotation());

	UE_LOG(LogTemp, Warning, TEXT("Direction : %f"), CurDirection);

	//2D Size == vector length XY
	CurrentPawnSpeed = Velocity.Size2D();

	FVector Acceleration = MovementComponent->GetCurrentAcceleration();
	if (Acceleration != FVector(0.0f, 0.0f, 0.0f) && CurrentPawnSpeed > 3.0f) {
		SholdMove = true;
	}
	else {
		SholdMove = false;
	}

}

void URPGGameAnimInstance::UpdateIsPawnFalling()
{
	IsFaliing = MovementComponent->IsFalling();
}

void URPGGameAnimInstance::UpdateWeapon()
{
	this->WeaponEnum = OwningCharacter->WeaponEnum;

}
