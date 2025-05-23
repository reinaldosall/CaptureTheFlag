#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

// Forward declarations
class UButton;

UCLASS()
class CAPTURETHEFLAG_API UMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    // Botões para "Host", "Join" e "Quit"
    UPROPERTY(meta = (BindWidget))
    UButton* HostButton;

    UPROPERTY(meta = (BindWidget))
    UButton* JoinButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitButton;  

private:
    // Funções chamadas quando os botões são pressionados
    UFUNCTION()
    void OnHostButtonPressed();

    UFUNCTION()
    void OnJoinButtonPressed();

    UFUNCTION()
    void OnQuitButtonPressed();  // Função para o botão Quit
};
