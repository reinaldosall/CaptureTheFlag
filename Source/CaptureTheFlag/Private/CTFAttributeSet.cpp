#include "CTFAttributeSet.h"
#include "Net/UnrealNetwork.h"

UCTFAttributeSet::UCTFAttributeSet() {}

void UCTFAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCTFAttributeSet, Stamina, OldValue);
}

void UCTFAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UCTFAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
}
