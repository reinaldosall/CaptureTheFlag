#include "CTFFlagActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "CTFCharacter.h"
#include "Net/UnrealNetwork.h"

ACTFFlagActor::ACTFFlagActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

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
	InitialLocation = GetActorLocation();
	InitialRotation = GetActorRotation();
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
	if (HasAuthority())
	{
		Multicast_ResetFlag();
	}
}

void ACTFFlagActor::Multicast_ResetFlag_Implementation()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocationAndRotation(InitialLocation, InitialRotation);
	SetActorEnableCollision(true);
	FlagHolder = nullptr;
}

void ACTFFlagActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACTFFlagActor, FlagHolder);
}
void ACTFFlagActor::DropFlag()
{
	if (FlagHolder)
	{
		UE_LOG(LogTemp, Warning, TEXT("Flag dropped by: %s"), *FlagHolder->GetName());
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		SetActorEnableCollision(true);
		FlagHolder = nullptr;
	}
}
