#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ETeam.h"
#include "CTFGameInstance.generated.h"

UCLASS()
class CAPTURETHEFLAG_API UCTFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	ETeam LastWinningTeam;
};
