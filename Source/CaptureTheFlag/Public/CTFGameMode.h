#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ETeam.h"  // Incluir o arquivo onde o ETeam é definido
#include "CTFGameMode.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ACTFGameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	void AssignTeam(APlayerState* PlayerState);
	void ReturnFlagToCenter();
	void CheckForMatchEnd();

	// Funções para aumentar a pontuação
	void OnScore(ETeam Team);  // Agora referenciando o ETeam correto

	// Variáveis para armazenar os pontos
	int32 RedScore;
	int32 BlueScore;

	// Variável para armazenar a referência ao FlagActor
	class AFlagActor* FlagActor;
};
