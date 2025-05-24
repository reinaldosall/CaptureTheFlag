#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTFGameHUDWidget.generated.h"

UCLASS()
class CAPTURETHEFLAG_API UCTFGameHUDWidget : public UUserWidget

{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ScoreText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TeamNameText;

    UPROPERTY(meta = (BindWidget))
    class UButton* DashButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* FireballButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DashCooldownText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* FireballCooldownText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* MatchTimerText;

    // Função opcional para atualizar o placar via C++
    void UpdateScore(int32 RedScore, int32 BlueScore);

    // Função para atualizar o nome do time
    void SetTeamName(FString TeamName);

    // Atualiza os cronômetros
    void UpdateCooldowns(float DashCD, float FireballCD);
    void UpdateMatchTimer(int32 SecondsRemaining);
};
