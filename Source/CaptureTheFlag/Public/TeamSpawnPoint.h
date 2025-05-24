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
	ATeamSpawnPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	ETeam Team;
};
