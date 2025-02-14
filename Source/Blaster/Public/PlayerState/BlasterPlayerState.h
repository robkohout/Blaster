// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BlasterPlayerState.generated.h"

class ABlasterPlayerController;
class ABlasterCharacter;
/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void AddToScore(float ScoreAmount);
	virtual void OnRep_Score() override;

private:
	ABlasterCharacter* Character;
	ABlasterPlayerController* Controller;
};
