#include "CTFGameMode.h"
#include "CTFPlayerState.h"
#include "CTFGameState.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameState.h"

ACTFGameMode::ACTFGameMode()
{
    // Defina as classes personalizadas
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Characters/BP_CTFCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;
    PlayerStateClass = ACTFPlayerState::StaticClass();
    GameStateClass = ACTFGameState::StaticClass();
}

void ACTFGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Iniciar qualquer lógica adicional quando o jogo começar
    // Por exemplo, exibir uma mensagem, inicializar variáveis, etc.
    UE_LOG(LogTemp, Warning, TEXT("Game has started!"));
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

        // Verifica os jogadores já conectados no GameState e conta quantos estão em cada time
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

        // Se o time vermelho tem menos ou igual jogadores que o time azul, o jogador vai para o time vermelho
        // Caso contrário, ele vai para o time azul
        ETeam AssignedTeam = (RedCount <= BlueCount) ? ETeam::Red : ETeam::Blue;
        PS->SetTeam(AssignedTeam);

        // Exibe no log para debugar
        UE_LOG(LogTemp, Warning, TEXT("Assigned to team: %s"), *UEnum::GetValueAsString(AssignedTeam));
    }
}

