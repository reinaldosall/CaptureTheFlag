#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CTFCharacter.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACTFCharacter();

protected:
	virtual void BeginPlay() override;

	// Movimento e câmera
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void StartJump();
	void StopJump();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USkeletalMeshComponent* Gun;
};