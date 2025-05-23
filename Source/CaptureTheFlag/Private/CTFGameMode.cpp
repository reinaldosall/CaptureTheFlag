#include "CTFGameMode.h"
#include "CTFPlayerState.h"
#include "CTFGameState.h"
#include "CTFCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/World.h" // Para instanciar a FlagActor

ACTFGameMode::ACTFGameMode()
{
    // Defina as classes personalizadas
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Characters/BP_CTFCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;

    PlayerStateClass = ACTFPlayerState::StaticClass();
    GameStateClass = ACTFGameState::StaticClass();

    // Inicialize o placar
    RedScore = 0;
    BlueScore = 0;

    // Inicialize a FlagActor
    FlagActor = nullptr;
}

void ACTFGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (NewPlayer && NewPlayer->PlayerState)
    {
        AssignTeam(NewPlayer->PlayerState);
    }
}

void ACTFGameMode::AssignTeam(APlayerState* PlayerState)
{
    // Atribui time ao jogador
    if (ACTFPlayerState* PS = Cast<ACTFPlayerState>(PlayerState))
    {
        int32 RedCount = 0;
        int32 BlueCount = 0;

        // Contabiliza jogadores nos times
        for (APlayerState* OtherState : GameState->PlayerArray)
        {
            if (const ACTFPlayerState* OtherPS = Cast<ACTFPlayerState>(OtherState))
            {
                if (OtherPS->Team == ETeam::Red)
                    RedCount++;
                else if (OtherPS->Team == ETeam::Blue)
                    BlueCount++;
            }
        }

        ETeam AssignedTeam = (RedCount <= BlueCount) ? ETeam::Red : ETeam::Blue;
        PS->SetTeam(AssignedTeam);

        if (GEngine)
        {
            FString TeamName = (AssignedTeam == ETeam::Red) ? TEXT("Red") : TEXT("Blue");
            GEngine->AddOnScreenDebugMessage(-1, 155.f, FColor::Green, FString::Printf(TEXT("%s joined the %s team."), *PS->GetPlayerName(), *TeamName));
        }
    }
}

void ACTFGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Instancia a FlagActor no mundo
    if (!FlagActor)
    {
        // Instancia a bandeira
        // Exemplo: FlagActor = GetWorld()->SpawnActor<AFlagActor>(FlagActorClass, SpawnLocation, SpawnRotation);
    }

    UE_LOG(LogTemp, Warning, TEXT("Game has started!"));
}
