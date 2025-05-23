#pragma once

#include "ETeam.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Red UMETA(DisplayName = "Red"),
	Blue UMETA(DisplayName = "Blue"),
	None UMETA(DisplayName = "None")
};
