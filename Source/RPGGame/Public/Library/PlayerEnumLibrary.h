#pragma once

#include "CoreMinimal.h"
#include "PlayerEnumLibrary.generated.h"

UENUM(BlueprintType)
enum class EPlayerMovementType : uint8
{
	Normal,
	Walk,
	Sprint,
	Jump,
	Fall,
	Roll,
	Dodge,
};

UENUM(BlueprintType)
enum class EPlayerStateType : uint8
{
	Locomotion,
	Fall,
	Roll,
	Dodge,
};
