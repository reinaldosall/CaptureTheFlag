#include "CTFGameState.h"
#include "Net/UnrealNetwork.h"

ACTFGameState::ACTFGameState()
{
	RedScore = 0;
	BlueScore = 0;
	bReplicates = true;
}

void ACTFGameState::AddScore(ETeam Team, int32 Amount)
{
	if (HasAuthority())
	{
		if (Team == ETeam::Red)
		{
			RedScore += Amount;
		}
		else if (Team == ETeam::Blue)
		{
			BlueScore += Amount;
		}
	}
}

void ACTFGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACTFGameState, RedScore);
	DOREPLIFETIME(ACTFGameState, BlueScore);
}
