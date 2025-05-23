#include "FlagActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "CTFCharacter.h"

AFlagActor::AFlagActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	FlagMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlagMesh"));
	SetRootComponent(FlagMesh);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetSphereRadius(100.f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AFlagActor::OnOverlapBegin);

	Carrier = nullptr;
}

void AFlagActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFlagActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority() && Carrier == nullptr)
	{
		ACTFCharacter* Character = Cast<ACTFCharacter>(OtherActor);
		if (Character)
		{
			Carrier = Character;
			AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("FlagSocket")); // Certifique-se de que o socket exista na malha
		}
	}
}

void AFlagActor::DropFlag()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Carrier = nullptr;
}

void AFlagActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFlagActor, Carrier);
}
