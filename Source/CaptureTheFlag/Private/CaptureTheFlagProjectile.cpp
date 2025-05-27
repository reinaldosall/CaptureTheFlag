// Copyright Epic Games, Inc. All Rights Reserved.

#include "CaptureTheFlagProjectile.h"
#include "EngineUtils.h" // Necessário para TActorIterator
#include "CTFFlagActor.h" // Para acessar ACTFFlagActor
#include "CTFGameMode.h" // Para acessar ACTFFlagActor
#include "CTFCharacter.h" // Para acessar ACTFFlagActor
#include "CTFPlayerController.h"
#include "GameFramework/Actor.h" // Geralmente necessário
#include "Engine/World.h" // Para GetWorld()
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ACaptureTheFlagProjectile::ACaptureTheFlagProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACaptureTheFlagProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ACaptureTheFlagProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	ACTFCharacter* HitCharacter = Cast<ACTFCharacter>(OtherActor);
	if (HitCharacter)
	{
		for (TActorIterator<ACTFFlagActor> It(GetWorld()); It; ++It)
		{
			ACTFFlagActor* Flag = *It;
			if(Flag && Flag->GetFlagHolder() == HitCharacter)
			{
				Flag->DropFlag();
			}
		}
	}

	if (HitCharacter && HitCharacter->HasAuthority() && !HitCharacter->bIsDead)
	{
		HitCharacter->bIsDead = true;
		AController* HitController = HitCharacter->GetController();

		if (HitController)
		{
			HitCharacter->DetachFromControllerPendingDestroy();
			HitCharacter->Destroy();

			int32 RespawnTime = 3;

			for (int32 i = RespawnTime; i >= 0; --i)
			{
				FTimerHandle CountdownHandle;
				HitController->GetWorldTimerManager().SetTimer(CountdownHandle, FTimerDelegate::CreateLambda([=]()
				{
					if (ACTFPlayerController* CTFPC = Cast<ACTFPlayerController>(HitController))
					{
						CTFPC->Client_UpdateRespawnCountdown(i);
					}

					if (i == 0)
					{
						if (ACTFGameMode* GM = Cast<ACTFGameMode>(HitController->GetWorld()->GetAuthGameMode()))
						{
							GM->RespawnPlayer(HitController);
						}
					}
				}), RespawnTime - i, false);
			}
		}
	}

	
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}