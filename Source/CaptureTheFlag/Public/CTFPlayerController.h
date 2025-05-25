#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CTFPlayerController.generated.h"

class UCTFGameHUDWidget;

UCLASS()
class CAPTURETHEFLAG_API ACTFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACTFPlayerController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCTFGameHUDWidget> GameHUDWidgetClass;

private:
	UPROPERTY()
	UCTFGameHUDWidget* GameHUDWidget;
};
