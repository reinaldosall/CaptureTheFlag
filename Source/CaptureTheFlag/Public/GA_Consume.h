#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Consume.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UGA_Consume : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	float CoolDown;	
};