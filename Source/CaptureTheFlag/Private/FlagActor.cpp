#include "FlagActor.h"
#include "Components/StaticMeshComponent.h"

AFlagActor::AFlagActor()
{
	PrimaryActorTick.bCanEverTick = true;

	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	RootComponent = FlagMesh;

	FlagMesh->SetSimulatePhysics(false);
	FlagMesh->SetEnableGravity(false);
	FlagMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FlagMesh->SetCollisionProfileName(TEXT("BlockAll"));
	FlagMesh->SetVisibility(true);
	FlagMesh->SetHiddenInGame(false);

	bReplicates = true;
	SetReplicatingMovement(true);
}

void AFlagActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation(); // Salva posição inicial real no BeginPlay
}

void AFlagActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlagActor::ReturnFlagToCenter()
{
	SetActorLocation(InitialLocation);
}
