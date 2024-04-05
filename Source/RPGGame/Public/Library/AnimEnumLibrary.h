#pragma once

#include "CoreMinimal.h"
#include "AnimEnumLibrary.generated.h"

UENUM(BlueprintType)
enum class ELocomotionCategory : uint8
{
	None,
	Idle,
	Jump,
	Fall,
	Walk_Run,
	Land,
};

UENUM(BlueprintType)
enum class EMontageCategory : uint8
{
	Default,
	Attack,
	React_Small,
	React_Large,
	Death,
	Guard,
};

UENUM(BlueprintType)
enum class EDirectionFromAngle : uint8
{
	Fwd,
	Bwd,
	Right,
	Left,
};

USTRUCT(BlueprintType)
struct FAnimDataArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UAnimationAsset*> AnimAssetList;

};


USTRUCT(BlueprintType)
struct FAnimLayerSelectSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (TitleProperty = Layer))
	TSubclassOf<UAnimInstance> EquipAnimLayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> DefaultLayer;

public:
	TSubclassOf<UAnimInstance> SelectBestLayer() const { return EquipAnimLayer != nullptr ? EquipAnimLayer : DefaultLayer; }
};

USTRUCT(BlueprintType)
struct FAnimMontageSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* EquipAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* UnEquipAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AttackAnim;

};