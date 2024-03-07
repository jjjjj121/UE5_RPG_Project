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
	TSubclassOf<UAnimInstance> LayerRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> DefaultLayer;

public:
	TSubclassOf<UAnimInstance> SelectBestLayer() const { return LayerRule != nullptr ? LayerRule : DefaultLayer; }
};
