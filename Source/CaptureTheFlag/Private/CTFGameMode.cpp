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

    // Inicialize a FlagActor (isso pode ser modificado dependendo de como você configura a FlagActor no seu projeto)
    FlagActor = nullptr; // Inicializa com nullptr. Você pode instanciar a bandeira no BeginPlay ou outro método.
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
    if (ACTFPlayerState* PS = Cast<ACTFPlayerState>(PlayerState))
    {
        int32 RedCount = 0;
        int32 BlueCount = 0;

        // Contabilizar jogadores nos times
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

        // Atribuir time ao jogador com base no número de jogadores
        ETeam AssignedTeam = (RedCount <= BlueCount) ? ETeam::Red : ETeam::Blue;

        // Definir o time para o jogador
        PS->SetTeam(AssignedTeam);

        // Mensagem de depuração para saber qual time foi atribuído
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

    // Inicializa a FlagActor no mundo
    if (!FlagActor)
    {
        // Instancia a FlagActor, se necessário. Aqui você pode usar o método para instanciar o ator
        // Exemplo: FlagActor = GetWorld()->SpawnActor<AFlagActor>(FlagActorClass, SpawnLocation, SpawnRotation);
    }

    // Outras configurações necessárias no início do jogo
    UE_LOG(LogTemp, Warning, TEXT("Game has started!"));
}
