#pragma once

#include "CoreMinimal.h"
#include "PlayerEnumLibrary.generated.h"

UENUM(BlueprintType)
enum class EPlayerMovementType : uint8
{
	Normal,
	Walk,
	Sprint,
};

