#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ETeam.h"
#include "CTFBaseZone.generated.h"

class UBoxComponent;

UCLASS()
class CAPTURETHEFLAG_API ACTFBaseZone : public AActor
{
	GENERATED_BODY()

public:
	ACTFBaseZone();

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	ETeam Team;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);
};
