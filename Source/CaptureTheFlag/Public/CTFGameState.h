#pragma once

#include "CoreMinimal.h"
#include "CTFPlayerController.h"
	
#include "GameFramework/GameState.h"
#include "ETeam.h"
#include "CTFGameState.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFGameState : public AGameState
{
	GENERATED_BODY()

public:
	ACTFGameState();

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 RedScore;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 BlueScore;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Score")
	ETeam LastWinningTeam;

	UPROPERTY(ReplicatedUsing = OnRep_MatchTime)
	int32 MatchTimeRemaining;

	UFUNCTION()
	void OnRep_MatchTime();
	
	void AddScore(ETeam Team, int32 Amount);
	void OnRep_LastWinningTeam();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
