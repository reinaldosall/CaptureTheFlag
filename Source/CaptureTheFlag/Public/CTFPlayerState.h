#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ETeam.h"
#include "CTFPlayerState.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ACTFPlayerState();

    UPROPERTY(ReplicatedUsing = OnRep_Team)
    ETeam Team;

    void SetTeam(ETeam NewTeam);

protected:
    UFUNCTION()
    void OnRep_Team();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
