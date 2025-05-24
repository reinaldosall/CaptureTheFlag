#include "CTFMainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"

ACTFMainMenuGameMode::ACTFMainMenuGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuWidgetBPClass(TEXT("/Game/Widgets/WBP_MainMenu"));
	if (MenuWidgetBPClass.Succeeded())
	{
		MainMenuWidgetClass = MenuWidgetBPClass.Class;
	}
}

void ACTFMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (MainMenuWidgetClass && World)
	{
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeUIOnly());

			MainMenuWidget = CreateWidget<UUserWidget>(PC, MainMenuWidgetClass);
			if (MainMenuWidget)
			{
				MainMenuWidget->AddToViewport();
			}
		}
	}
}

void ACTFMainMenuGameMode::HostGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Hosting a Game..."));

	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}

	UWorld* World = GetWorld();
	if (World)
	{
		TWeakObjectPtr<APlayerController> WeakPC = World->GetFirstPlayerController();

		World->GetTimerManager().SetTimerForNextTick([WeakPC]()
		{
			if (WeakPC.IsValid())
			{
				WeakPC->SetInputMode(FInputModeGameOnly());
				WeakPC->bShowMouseCursor = false;
			}
		});

		UGameplayStatics::OpenLevel(World, FName(TEXT("FirstPersonMap")), true, TEXT("listen"));
	}
}

void ACTFMainMenuGameMode::JoinGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Joining an Existing Game..."));

	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}

	UWorld* World = GetWorld();
	if (World)
	{
		TWeakObjectPtr<APlayerController> WeakPC = World->GetFirstPlayerController();

		World->GetTimerManager().SetTimerForNextTick([WeakPC]()
		{
			if (WeakPC.IsValid())
			{
				WeakPC->SetInputMode(FInputModeGameOnly());
				WeakPC->bShowMouseCursor = false;
			}
		});

		UGameplayStatics::OpenLevel(World, FName(TEXT("127.0.0.1")));
	}
}
