#include "CTFPlayerController.h"
#include "CTFGameInstance.h"
#include "CTFGameState.h"
#include "CTFGameHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ACTFPlayerController::ACTFPlayerController()
{
	static ConstructorHelpers::FClassFinder<UCTFGameHUDWidget> HUDWidgetClass(TEXT("/Game/Widgets/WBP_GameHUD"));
	if (HUDWidgetClass.Succeeded())
	{
		GameHUDWidgetClass = HUDWidgetClass.Class;
	}
}

void ACTFPlayerController::Client_SetWinningTeam_Implementation(ETeam WinningTeam)
{
	if (UCTFGameInstance* GI = Cast<UCTFGameInstance>(GetGameInstance()))
	{
		GI->LastWinningTeam = WinningTeam;
		UE_LOG(LogTemp, Warning, TEXT("[CLIENT] GameInstance atualizado via RPC: %s"), *UEnum::GetValueAsString(WinningTeam));
	}
}

void ACTFPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocalController() && GameHUDWidget)
	{
		ACTFGameState* GS = GetWorld()->GetGameState<ACTFGameState>();
		if (GS)
		{
			GameHUDWidget->UpdateMatchTimer(GS->MatchTimeRemaining);
			GameHUDWidget->UpdateScore(GS->RedScore, GS->BlueScore);
		}
	}
}
void ACTFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	FString MapName = GetWorld()->GetMapName();
	
	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay | HasAuthority: %s | IsLocalController: %s"),
		HasAuthority() ? TEXT("true") : TEXT("false"),
		IsLocalController() ? TEXT("true") : TEXT("false"));

	if (IsLocalController())
	{
		if (GameHUDWidgetClass && MapName.Contains("FirstPerson"))
		{
			GameHUDWidget = CreateWidget<UCTFGameHUDWidget>(this, GameHUDWidgetClass);
			if (GameHUDWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("HUD widget criado com sucesso"));
				GameHUDWidget->AddToViewport();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Falha ao criar HUD widget"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GameHUDWidgetClass é nullptr"));
		}
	}
	
}

