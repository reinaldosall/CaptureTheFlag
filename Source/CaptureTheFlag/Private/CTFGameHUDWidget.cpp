#include "CTFGameHUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UCTFGameHUDWidget::UpdateScore(int32 RedScore, int32 BlueScore)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Red: %d x %d Blue"), RedScore, BlueScore)));
	}
}

void UCTFGameHUDWidget::SetTeamName(FString TeamName)
{
	if (TeamNameText)
	{
		TeamNameText->SetText(FText::FromString(FString::Printf(TEXT("You are on the %s Team"), *TeamName)));
	}
}

void UCTFGameHUDWidget::UpdateCooldowns(float DashCD, float FireballCD)
{
	if (DashCooldownText)
	{
		DashCooldownText->SetText(FText::FromString(FString::Printf(TEXT("%.1fs"), DashCD)));
	}

	if (FireballCooldownText)
	{
		FireballCooldownText->SetText(FText::FromString(FString::Printf(TEXT("%.1fs"), FireballCD)));
	}
}

void UCTFGameHUDWidget::UpdateMatchTimer(int32 SecondsRemaining)
{
	if (MatchTimerText)
	{
		int32 Minutes = SecondsRemaining / 60;
		int32 Seconds = SecondsRemaining % 60;
		MatchTimerText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}
