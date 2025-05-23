#include "CTFMainMenuGameMode.h"
#include "CTFPlayerState.h"
#include "CTFGameState.h"
#include "CTFCharacter.h"
#include "MainMenuWidget.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ACTFMainMenuGameMode::ACTFMainMenuGameMode()
{
    // Definindo as classes de PlayerState e GameState
    PlayerStateClass = ACTFPlayerState::StaticClass();
    GameStateClass = ACTFGameState::StaticClass();

    // Definindo o personagem (Pawn) que será usado no jogo
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Characters/BP_CTFCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void ACTFMainMenuGameMode::BeginPlay()
{
    Super::BeginPlay();
    // Lógica do início do jogo, como exibir uma mensagem ou iniciar alguma função
    UE_LOG(LogTemp, Warning, TEXT("Main Menu Game Mode Started!"));

    if (UWorld* World = GetWorld())
    {
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if (PlayerController)
        {
            UMainMenuWidget* MainMenu = CreateWidget<UMainMenuWidget>(PlayerController, UMainMenuWidget::StaticClass());
            if (MainMenu)
            {
                MainMenu->AddToViewport();  // Exibe o Widget na tela
            }
        }
    }
}

void ACTFMainMenuGameMode::HostGame()
{
    // Função chamada quando o jogador escolhe "Host"
    // Inicia o servidor de jogos, criando uma nova sessão
    UE_LOG(LogTemp, Warning, TEXT("Hosting a Game..."));
    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("FirstPersonMap")));
}

void ACTFMainMenuGameMode::JoinGame()
{
    // Função chamada quando o jogador escolhe "Join"
    // Inicia o processo de juntar-se a uma sessão existente
    UE_LOG(LogTemp, Warning, TEXT("Joining an Existing Game..."));
    // Aqui você pode colocar a lógica para encontrar e conectar-se a uma sessão existente
}

void ACTFMainMenuGameMode::AssignTeam(APlayerState* PlayerState)
{
    // Atribui os times com base na quantidade de jogadores
    if (ACTFPlayerState* PS = Cast<ACTFPlayerState>(PlayerState))
    {
        int32 RedCount = 0;
        int32 BlueCount = 0;

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
    }
}
