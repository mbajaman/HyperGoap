#pragma once
#include "CoreMinimal.h"

enum class EDirection
{
	Forward,
	Right,
	Back,
	Left,
	Up,
	Down
};

UENUM(BlueprintType)
enum class EBlock : uint8
{
	Null,
	Air,
	Grassland,
	Village,
	AbandonedBuilding,
	Pond
};

UENUM(BlueprintType)
enum class States : uint8
{
	Grassland,
	Village,
	AbandonedBuilding,
	Pond
};