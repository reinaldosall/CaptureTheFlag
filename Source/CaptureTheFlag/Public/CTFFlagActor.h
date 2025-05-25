#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTFFlagActor.generated.h"

class USphereComponent;
class ACTFCharacter;

UCLASS()
class CAPTURETHEFLAG_API ACTFFlagActor : public AActor
{
	GENERATED_BODY()

public:
	ACTFFlagActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnFlagOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
					   bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FlagMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComponent;

	UPROPERTY()
	ACTFCharacter* FlagHolder;

public:
	virtual void Tick(float DeltaTime) override;
	void ReturnFlagToCenter();
public:
	ACTFCharacter* GetFlagHolder() const { return FlagHolder; }
	
private:
	FVector InitialLocation;
	FRotator InitialRotation;
};