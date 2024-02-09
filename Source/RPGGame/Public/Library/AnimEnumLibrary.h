#pragma once

#include "CoreMinimal.h"
#include "AnimEnumLibrary.generated.h"

UENUM(BlueprintType)
enum class ELocomotion : uint8
{
	None,
	Idle,
	Jump,
	Fall,
	Walk_Run,
	Land,
};


USTRUCT(BlueprintType)
struct FAnimDataArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UAnimationAsset*> AnimAssetList;

};
