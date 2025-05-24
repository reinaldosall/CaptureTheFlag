#include "CTFGameMode.h"
#include "CTFPlayerState.h"
#include "CTFGameState.h"
#include "FlagActor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "TeamSpawnPoint.h"
#include "EngineUtils.h"
#include "Engine/World.h" 

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

AActor* ACTFGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
    if (APlayerState* PS = Player->PlayerState)
    {
        if (ACTFPlayerState* CTFPS = Cast<ACTFPlayerState>(PS))
        {
            for (TActorIterator<ATeamSpawnPoint> It(GetWorld()); It; ++It)
            {
                if (It->Team == CTFPS->Team)
                {
                    return *It;
                }
            }
        }
    }

    // fallback se nada for encontrado
    return Super::ChoosePlayerStart_Implementation(Player);
}

void ACTFGameMode::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->SetInputMode(FInputModeGameOnly());
        PC->bShowMouseCursor = false;
    }

    // Detecta e referencia uma bandeira já existente no mapa
    TArray<AActor*> FoundFlags;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFlagActor::StaticClass(), FoundFlags);

    if (FoundFlags.Num() > 0)
    {
        FlagActor = Cast<AFlagActor>(FoundFlags[0]);
        UE_LOG(LogTemp, Warning, TEXT("Bandeira existente encontrada no mapa."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Nenhuma bandeira encontrada no mapa!"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Game has started!"));
}
