#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlagActor.generated.h"

UCLASS()
class CAPTURETHEFLAG_API AFlagActor : public AActor
{
	GENERATED_BODY()

public:
	AFlagActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Função para retornar a bandeira ao centro do mapa
	void ReturnFlagToCenter();

private:
	// Localização inicial do centro da bandeira
	FVector InitialLocation;
};
