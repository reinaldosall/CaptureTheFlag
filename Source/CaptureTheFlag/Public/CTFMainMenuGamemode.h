#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CTFMainMenuGameMode.generated.h"

UCLASS()
class CAPTURETHEFLAG_API ACTFMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ACTFMainMenuGameMode();

protected:
	virtual void BeginPlay() override;

public:
	void HostGame();
	void JoinGame();

private:
	UPROPERTY()
	class UUserWidget* MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;
};
