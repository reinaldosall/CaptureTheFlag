#include "CTFPlayerState.h"
#include "Net/UnrealNetwork.h"

ACTFPlayerState::ACTFPlayerState()
{
    bReplicates = true;
}

void ACTFPlayerState::SetTeam(ETeam NewTeam)
{
    if (HasAuthority())
    {
        Team = NewTeam;
        OnRep_Team();
    }
}

void ACTFPlayerState::OnRep_Team()
{
    // Handle visual or logic changes when team changes (if needed)
}

void ACTFPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ACTFPlayerState, Team);
}
