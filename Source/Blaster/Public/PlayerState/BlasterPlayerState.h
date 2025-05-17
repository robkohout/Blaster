// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "BlasterTypes/Team.h"
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
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	/*
	 * Replication notifies
	 */
	virtual void OnRep_Score() override;
	
	UFUNCTION()
	virtual void OnRep_Defeats();

	void AddToScore(float ScoreAmount);
	void AddToDefeats(int32 DefeatsAmount);
	
private:
	UPROPERTY()
	ABlasterCharacter* Character;
	UPROPERTY()
	ABlasterPlayerController* Controller;

	UPROPERTY(ReplicatedUsing=OnRep_Defeats)
	int32 Defeats;

	UPROPERTY(ReplicatedUsing=OnRep_Team)
	ETeam Team = ETeam::ET_NoTeam;

	UFUNCTION()
	void OnRep_Team();
public:
	FORCEINLINE ETeam GetTeam() const { return Team; }
	void SetTeam(ETeam TeamToSet);
};