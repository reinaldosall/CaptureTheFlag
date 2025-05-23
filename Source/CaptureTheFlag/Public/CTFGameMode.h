#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ETeam.h"
#include "CTFGameHUDWidget.h"
#include "CTFGameMode.generated.h"

class ACTFFlagActor;

UCLASS()
class CAPTURETHEFLAG_API ACTFGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ACTFGameMode();
	
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	void AssignTeam(APlayerState* PlayerState);

protected:
	int32 RedScore;
	int32 BlueScore;

	UPROPERTY()
	ACTFFlagActor* FlagActor;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCTFGameHUDWidget> GameHUDWidgetClass;
};
