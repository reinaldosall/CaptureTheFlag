#include "CTFGameState.h"
#include "CTFGameHUDWidget.h"
#include "CTFGameInstance.h"
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
void ACTFGameState::OnRep_LastWinningTeam()
{
	if (UCTFGameInstance* GI = Cast<UCTFGameInstance>(GetGameInstance()))
	{
		GI->LastWinningTeam = LastWinningTeam;

		UE_LOG(LogTemp, Warning, TEXT("[CLIENT] LastWinningTeam atualizado para: %s"),
			*UEnum::GetValueAsString(LastWinningTeam));
	}
}

void ACTFGameState::OnRep_MatchTime()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (ACTFPlayerController* CTFPC = Cast<ACTFPlayerController>(PC))
		{
			if (CTFPC->GetGameHUDWidget())
			{
				CTFPC->GetGameHUDWidget()->UpdateMatchTimer(MatchTimeRemaining);
			}
		}
	}
}


void ACTFGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACTFGameState, LastWinningTeam);
	DOREPLIFETIME(ACTFGameState, MatchTimeRemaining);
	DOREPLIFETIME(ACTFGameState, RedScore);
	DOREPLIFETIME(ACTFGameState, BlueScore);
}
