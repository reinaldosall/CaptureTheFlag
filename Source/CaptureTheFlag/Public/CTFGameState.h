#pragma once

#include "CoreMinimal.h"
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

	void AddScore(ETeam Team, int32 Amount);
	void OnRep_LastWinningTeam();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
