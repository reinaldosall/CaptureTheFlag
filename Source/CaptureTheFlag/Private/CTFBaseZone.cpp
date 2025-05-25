#include "CTFBaseZone.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"
#include "CTFCharacter.h"
#include "CTFFlagActor.h"
#include "CTFGameMode.h"
#include "CTFPlayerState.h"
#include "Kismet/GameplayStatics.h"

ACTFBaseZone::ACTFBaseZone()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACTFBaseZone::OnOverlapBegin);
}

void ACTFBaseZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								  bool bFromSweep, const FHitResult& SweepResult)
{
	ACTFCharacter* Character = Cast<ACTFCharacter>(OtherActor);
	if (Character)
	{
		ACTFPlayerState* PS = Cast<ACTFPlayerState>(Character->GetPlayerState());
		if (PS && PS->Team == Team)
		{
			for (TActorIterator<ACTFFlagActor> It(GetWorld()); It; ++It)
			{
				ACTFFlagActor* Flag = *It;
				if (Flag->GetFlagHolder() == Character)
				{
					if (ACTFGameMode* GM = Cast<ACTFGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
					{
						GM->HandleFlagCapture(Cast<ACTFCharacter>(OtherActor));
					}
					break;
				}
			}
		}
	}
}
