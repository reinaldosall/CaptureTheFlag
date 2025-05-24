#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ETeam.h"
#include "TeamSpawnPoint.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ATeamSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Team")
	ETeam Team;

	ATeamSpawnPoint();
};
