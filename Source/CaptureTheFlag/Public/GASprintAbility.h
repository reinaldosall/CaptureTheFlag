#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GASprintAbility.generated.h"

UCLASS()
class CAPTURETHEFLAG_API UGASprintAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGASprintAbility();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;

protected:
	float OriginalSpeed;
};
