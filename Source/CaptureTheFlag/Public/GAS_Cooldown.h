// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GAS_Cooldown.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURETHEFLAG_API UGAS_Cooldown : public UGameplayModMagnitudeCalculation
{
GENERATED_BODY()
	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
};
