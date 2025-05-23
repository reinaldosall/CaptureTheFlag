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
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* FlagMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* CollisionSphere;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(Replicated)
	class ACTFCharacter* Carrier;

	void DropFlag();
};
