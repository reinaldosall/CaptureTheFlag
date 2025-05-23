#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CTFGameMode.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ACTFGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	void AssignTeam(class APlayerState* PlayerState);
};
