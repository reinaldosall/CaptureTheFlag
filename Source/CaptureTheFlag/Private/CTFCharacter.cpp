#include "CTFCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "CTFPlayerState.h" 

ACTFCharacter::ACTFCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Câmera
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(GetCapsuleComponent());
    CameraComponent->bUsePawnControlRotation = true;
    CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 64.f));

    // Malha de primeira pessoa
    Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
    Mesh1P->SetupAttachment(CameraComponent);
    Mesh1P->bCastDynamicShadow = false;
    Mesh1P->CastShadow = false;
    Mesh1P->SetOnlyOwnerSee(true);
    Mesh1P->SetRelativeLocation(FVector(0.f, 0.f, -160.f));
    Mesh1P->SetRelativeRotation(FRotator(2.f, -15.f, 5.f));

    // Arma
    Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
    Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
    Gun->bCastDynamicShadow = false;
    Gun->CastShadow = false;
    Gun->SetOnlyOwnerSee(true);

    // Movimento
    bUseControllerRotationYaw = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;
}

void ACTFCharacter::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Character spawned at location: %s"), *GetActorLocation().ToString());

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (IsLocallyControlled())
    {
        UE_LOG(LogTemp, Warning, TEXT("Character is locally controlled and possessed by: %s"), *GetNameSafe(PC));
    }
    
    if (!IsLocallyControlled())
    {
        Mesh1P->SetVisibility(false, true);
        Gun->SetVisibility(false, true);
    }
    else
    {
        if (ACTFPlayerState* PS = Cast<ACTFPlayerState>(GetPlayerState()))
        {
            FString TeamName = (PS->Team == ETeam::Red) ? TEXT("Red") : TEXT("Blue");
            GEngine->AddOnScreenDebugMessage(-1, 155.f, FColor::Yellow, FString::Printf(TEXT("You are on the %s Team"), *TeamName));
        }
    }
}

void ACTFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ACTFCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ACTFCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ACTFCharacter::LookUp);
    PlayerInputComponent->BindAxis("Turn", this, &ACTFCharacter::Turn);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACTFCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACTFCharacter::StopJump);
}

void ACTFCharacter::MoveForward(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void ACTFCharacter::MoveRight(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void ACTFCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void ACTFCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ACTFCharacter::StartJump()
{
    bPressedJump = true;
}

void ACTFCharacter::StopJump()
{
    bPressedJump = false;
}
