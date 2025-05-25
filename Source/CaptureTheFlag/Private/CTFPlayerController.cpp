#include "CTFPlayerController.h"
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

void ACTFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay | HasAuthority: %s | IsLocalController: %s"),
		HasAuthority() ? TEXT("true") : TEXT("false"),
		IsLocalController() ? TEXT("true") : TEXT("false"));

	if (IsLocalController())
	{
		if (GameHUDWidgetClass)
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