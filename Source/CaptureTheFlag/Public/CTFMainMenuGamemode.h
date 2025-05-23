#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CTFMainMenuGameMode.generated.h"

// Forward declarations
class APlayerController;
class APlayerState;

UCLASS()
class CAPTURETHEFLAG_API ACTFMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACTFMainMenuGameMode();

protected:
	virtual void BeginPlay() override;

public:
	// Funções para host e join
	void HostGame();
	void JoinGame();

	// Função para atribuir os times aos jogadores
	void AssignTeam(APlayerState* PlayerState);
};
