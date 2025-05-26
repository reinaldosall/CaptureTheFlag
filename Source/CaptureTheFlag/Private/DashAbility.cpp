#include "DashAbility.h"
#include "CooldownEffect_Dash.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UDashAbility::UDashAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	// Cooldown tag para UI e controle
	CooldownGameplayEffectClass = UCooldownEffect_Dash::StaticClass();
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Dash")));
	CooldownTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Cooldown.Dash")));
}

void UDashAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (Character)
	{
		FVector DashDir = Character->GetActorForwardVector();
		Character->LaunchCharacter(DashDir * DashStrength, true, true);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UDashAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
