// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS_Cooldown.h"
#include "GA_Consume.h"

float UGAS_Cooldown::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UGA_Consume* Ability = Cast<UGA_Consume>(Spec.GetContext().GetAbility());
	if (!Ability)
	{
		return 0.1f;
	}

	return Ability->CoolDown;
}
