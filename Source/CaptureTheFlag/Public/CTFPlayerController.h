#pragma once

#include "CoreMinimal.h"
#include "ETeam.h"
#include "GameFramework/PlayerController.h"
#include "CTFPlayerController.generated.h"

class UCTFGameHUDWidget;

UCLASS()
class CAPTURETHEFLAG_API ACTFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACTFPlayerController();

	UFUNCTION(Client, Reliable)
	void Client_SetWinningTeam(ETeam WinningTeam);
	void Client_SetWinningTeam_Implementation(ETeam WinningTeam);
	
	UFUNCTION(Client, Reliable)
	void Client_UpdateRespawnCountdown(int32 Time);
	
	virtual void Tick(float DeltaTime) override;
	UCTFGameHUDWidget* GetGameHUDWidget() const { return GameHUDWidget; }	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCTFGameHUDWidget> GameHUDWidgetClass;

private:
	UPROPERTY()
	UCTFGameHUDWidget* GameHUDWidget;
};
