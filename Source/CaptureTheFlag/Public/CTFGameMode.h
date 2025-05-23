#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ETeam.h"
#include "CTFGameMode.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACTFGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;

protected:
	void AssignTeam(APlayerState* PlayerState);

	int32 RedScore;
	int32 BlueScore;

	class AFlagActor* FlagActor;
};
