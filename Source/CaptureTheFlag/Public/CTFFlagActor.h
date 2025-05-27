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

	UPROPERTY(Replicated)
	ACTFCharacter* FlagHolder;

public:
	virtual void Tick(float DeltaTime) override;
	void ReturnFlagToCenter();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_ResetFlag();
	void Multicast_ResetFlag_Implementation();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	ACTFCharacter* GetFlagHolder() const { return FlagHolder; }

	UFUNCTION(BlueprintCallable)
	void DropFlag();

private:
	FVector InitialLocation;
	FRotator InitialRotation;
};
