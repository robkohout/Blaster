// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameMode/BlasterGameMode.h"
#include "TeamsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ATeamsGameMode : public ABlasterGameMode
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	
protected:
	virtual void HandleMatchHasStarted() override; 	
};
