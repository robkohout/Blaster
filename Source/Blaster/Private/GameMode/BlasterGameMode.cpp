// Copyright Rob Kohout

#include "GameMode/BlasterGameMode.h"
#include "GameFramework/PlayerState.h"


void ABlasterGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if(GEngine)
	{
		APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
		if(PlayerState)
		{
			FString PlayerName = PlayerState->GetPlayerName();			
		
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString::Printf(TEXT("%s has joined the game!"), *PlayerName)
				);
		}
	}
}

void ABlasterGameMode::PlayerEliminated(ABlasterCharacter* EliminatedCharacter,
	ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	
}
