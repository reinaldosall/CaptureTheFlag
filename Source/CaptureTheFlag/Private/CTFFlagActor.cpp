#include "CTFFlagActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CTFCharacter.h"

ACTFFlagActor::ACTFFlagActor()
{
	PrimaryActorTick.bCanEverTick = true;

	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	RootComponent = FlagMesh;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetSphereRadius(100.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACTFFlagActor::OnFlagOverlap);

	FlagHolder = nullptr;
}

void ACTFFlagActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACTFFlagActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACTFFlagActor::OnFlagOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								   bool bFromSweep, const FHitResult& SweepResult)
{
	if (FlagHolder != nullptr)
		return;

	ACTFCharacter* Character = Cast<ACTFCharacter>(OtherActor);
	if (Character)
	{
		FlagHolder = Character;
		AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("FlagSocket"));
		SetActorEnableCollision(false);
	}
}

void ACTFFlagActor::ReturnFlagToCenter()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocation(FVector(1510.f, 1600.f, 90.f)); // Altere conforme necessário
	SetActorEnableCollision(true);
	FlagHolder = nullptr;
}
