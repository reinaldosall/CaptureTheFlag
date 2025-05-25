#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CTFGameHUDWidget.generated.h"

UCLASS()
class CAPTURETHEFLAG_API UCTFGameHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

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

    void UpdateScore(int32 RedScore, int32 BlueScore);
    void SetTeamName(FString TeamName);
    void UpdateCooldowns(float DashCD, float FireballCD);
    void UpdateMatchTimer(int32 SecondsRemaining);
};
