#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTFFlagActor.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFFlagActor : public AActor
{
	GENERATED_BODY()

public:
	ACTFFlagActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void ReturnFlagToCenter();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FlagMesh;

	FVector InitialLocation;
};
