#include "FlagActor.h"
#include "Engine/World.h"

AFlagActor::AFlagActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Defina a localização inicial como o centro do mapa
	InitialLocation = FVector(0.f, 0.f, 100.f); // Ajuste as coordenadas conforme necessário
}

void AFlagActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Coloque a bandeira na posição inicial ao começar
	SetActorLocation(InitialLocation);
}

void AFlagActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlagActor::ReturnFlagToCenter()
{
	// Retorne a bandeira à localização inicial
	SetActorLocation(InitialLocation);
}
