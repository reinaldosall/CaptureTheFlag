#include "CTFFlagActor.h"
#include "Components/StaticMeshComponent.h"

ACTFFlagActor::ACTFFlagActor()
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

void ACTFFlagActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation(); // Salva posição inicial real no BeginPlay
}

void ACTFFlagActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTFFlagActor::ReturnFlagToCenter()
{
	SetActorLocation(InitialLocation);
}
