#include "CTFGameMode.h"
#include "CTFPlayerState.h"
#include "CTFGameState.h"
#include "CTFPlayerController.h"
#include "CTFFlagActor.h"
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
    
    PlayerControllerClass = ACTFPlayerController::StaticClass();
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

        AActor* StartSpot = ChoosePlayerStart(NewPlayer);
        RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
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
    if (Player && Player->PlayerState)
    {
        if (ACTFPlayerState* PS = Cast<ACTFPlayerState>(Player->PlayerState))
        {
            ETeam Team = PS->Team;

            for (TActorIterator<ATeamSpawnPoint> It(GetWorld()); It; ++It)
            {
                if (It->Team == Team)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Spawning %s at %s"), *UEnum::GetValueAsString(Team), *It->GetActorLocation().ToString());
                    return *It;
                }
            }
        }
    }

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

    TArray<AActor*> FoundFlags;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACTFFlagActor::StaticClass(), FoundFlags);

    if (FoundFlags.Num() > 0)
    {
        FlagActor = Cast<ACTFFlagActor>(FoundFlags[0]);
        UE_LOG(LogTemp, Warning, TEXT("Bandeira existente encontrada no mapa."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Nenhuma bandeira encontrada no mapa!"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Game has started!"));
}

