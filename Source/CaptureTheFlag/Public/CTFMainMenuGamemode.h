#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ETeam.h"
#include "CTFMainMenuGameMode.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACTFMainMenuGameMode();

	virtual void BeginPlay() override;

	void HostGame();
	void JoinGame();

protected:
	void AssignTeam(APlayerState* PlayerState);
};
