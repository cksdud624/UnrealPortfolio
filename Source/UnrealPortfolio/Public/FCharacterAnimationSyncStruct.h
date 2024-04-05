#pragma once

#include "FCharacterAnimationSyncStruct.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAnimationSyncStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsRunning;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Velocity;
};
