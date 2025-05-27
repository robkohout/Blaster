// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameMode/TeamsGameMode.h"
#include "CaptureTheFlagGameMode.generated.h"

class AFlagZone;
class AFlag;
/**
 * 
 */
UCLASS()
class BLASTER_API ACaptureTheFlagGameMode : public ATeamsGameMode
{
	GENERATED_BODY()

public:
	virtual void PlayerEliminated(ABlasterCharacter* EliminatedCharacter,
		ABlasterPlayerController* VictimController,
		ABlasterPlayerController* AttackerController) override;
	void FlagCaptured(AFlag* Flag, AFlagZone* Zone);
};
