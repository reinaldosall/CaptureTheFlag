#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "CTFMainMenuGameMode.h"  // Alterado para usar o novo GameMode CTFMainMenuGameMode

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Certifique-se de que os botões estão configurados corretamente
    if (HostButton)
    {
        HostButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnHostButtonPressed);
    }

    if (JoinButton)
    {
        JoinButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnJoinButtonPressed);
    }

    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitButtonPressed);  // Configura o botão Quit
    }
}

void UMainMenuWidget::OnHostButtonPressed()
{
    // Lógica para o botão de "Host Game"
    ACTFMainMenuGameMode* GameMode = Cast<ACTFMainMenuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {
        GameMode->HostGame();  // Chama a função que lida com o hosting
    }
}

void UMainMenuWidget::OnJoinButtonPressed()
{
    // Lógica para o botão de "Join Game"
    ACTFMainMenuGameMode* GameMode = Cast<ACTFMainMenuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (GameMode)
    {
        GameMode->JoinGame();  // Chama a função que lida com o join
    }
}

void UMainMenuWidget::OnQuitButtonPressed()
{
    // Lógica para o botão "Quit"
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);  // Fecha o jogo
}
