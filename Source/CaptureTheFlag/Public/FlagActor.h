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
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void ReturnFlagToCenter();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FlagMesh;

	FVector InitialLocation;
};
