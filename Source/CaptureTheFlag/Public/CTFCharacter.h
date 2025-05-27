#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GameFramework/Character.h"
#include "CTFCharacter.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACTFCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

protected:
	virtual void BeginPlay() override;

	//GAS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	UFUNCTION()
	void ActivateDash();

	// Movimento e câmera
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void StartJump();
	void StopJump();
	void Fire();

	UFUNCTION(Server, Reliable)
	void ServerFire();

	UFUNCTION()
	void OnFirePressed();

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	USceneComponent* MuzzleLocation;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsDead = false;	

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USkeletalMeshComponent* Gun;	
};