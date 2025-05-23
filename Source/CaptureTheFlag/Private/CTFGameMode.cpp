#include "CTFGameMode.h"
#include "CTFPlayerState.h"
#include "CTFGameState.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"

ACTFGameMode::ACTFGameMode()
{
	PlayerStateClass = ACTFPlayerState::StaticClass();
	GameStateClass = ACTFGameState::StaticClass();

	// Usa o Blueprint visual do personagem como pawn padrão
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_CTFCharacter"));

	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
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
