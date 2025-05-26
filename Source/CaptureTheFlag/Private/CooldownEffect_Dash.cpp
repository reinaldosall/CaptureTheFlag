#include "CooldownEffect_Dash.h"

UCooldownEffect_Dash::UCooldownEffect_Dash()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(3.0f); // Duração de 3 segundos

	// Adiciona a tag que identifica o cooldown
	InheritableOwnedTagsContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Cooldown.Dash")));
}
