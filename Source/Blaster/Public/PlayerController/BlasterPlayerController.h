// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

class ABlasterGameState;
class ABlasterPlayerState;
class UReturnToMainMenu;
class UInputAction;
class ABlasterGameMode;
class UCharacterOverlay;
class ABlasterHUD;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHighPingDelegate, bool, bPingTooHigh);

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDShield(float Shield, float MaxShield);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int Defeats);
	void SetHUDEliminated(FString AttackerName);
	void HideEliminated();
	void SetHUDWeaponAmmo(int Ammo);
	void SetHUDCarriedAmmo(int Ammo);
	void SetHUDMatchCountdown(float CountdownTime);
	void SetHUDAnnouncementCountdown(float CountdownTime);
	void SetHUDGrenades(int32 Grenades);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual float GetServerTime();  // Synced with server world clock
	virtual void ReceivedPlayer() override;  // Sync with server clock as soon as possible
	void OnMatchStateSet(FName State, bool bTeamsMatch = false);
	void HandleMatchHasStarted(bool bTeamsMatch = false);
	void HandleCooldown();
	void HideTeamScores();
	void InitTeamScores();
	void SetHUDRedTeamScore(int32 RedScore);
	void SetHUDBlueTeamScore(int32 BlueScore);

	float SingleTripTime = 0.f;

	FHighPingDelegate HighPingDelegate;
	
	void BroadcastElim(APlayerState* Attacker, APlayerState* Victim);
	
protected:
	virtual void BeginPlay() override;
	void SetHUDTime();
	void PollInit();

	virtual void SetupInputComponent() override;
	
	/*
	 * Sync time between client and server
	 */

	// Requests the current server time, passing in the client's time when the request was sent
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);

	// Reports the current server time to the client in response to ServerRequestServerTime
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);
	
	float ClientServerDelta = 0.f; // difference between client and server time 

	UPROPERTY(EditAnywhere, Category = Time)
	float TimeSyncFrequency = 5.f;

	float TimeSyncRunningTime = 0.f;
	void CheckTimeSync(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client, Reliable)
	void ClientJoinMidGame(FName StateOfMatch, float Warmup, float Match, float Cooldown, float StartingTime);

	void HighPingWarning();
	void StopHighPingWarning();
	void CheckPing(float DeltaTime);

	void ShowReturnToMainMenu();

	UFUNCTION(Client, Reliable)
	void ClientElimAnnouncement(APlayerState* Attacker, APlayerState* Victim);

	UPROPERTY(ReplicatedUsing=OnRep_ShowTeamScores)
	bool bShowTeamScores = false;

	UFUNCTION()
	void OnRep_ShowTeamScores();

	FString GetInfoText(const TArray<ABlasterPlayerState*>& Players);
	FString GetTeamsInfoText(ABlasterGameState* BlasterGameState);
	
private:
	UPROPERTY()
	ABlasterHUD* BlasterHUD;

	/*
	 * Return to Main Menu
	 */

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UUserWidget> ReturnToMainMenuWidget;

	UPROPERTY()
	UReturnToMainMenu* ReturnToMainMenu;

	bool bReturnToMainMenuOpen = false;
	
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* QuitAction;
	
	UPROPERTY()
	ABlasterGameMode* BlasterGameMode;
	float LevelStartingTime = 0.f;
	float MatchTime = 0.f;
	float WarmupTime = 0.f;
	float CooldownTime = 0.f;
	uint32 CountdownInt = 0;

	UPROPERTY(ReplicatedUsing=OnRep_MatchState)
	FName MatchState;

	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;
		
	float HUDHealth;
	float HUDMaxHealth;
	bool bInitializeHealth = false;
	float HUDShield;
	float HUDMaxShield;
	bool bInitializeShield = false;
	float HUDScore;
	bool bInitializeScore = false;
	int32 HUDDefeats;
	bool bInitializeDefeats = false;
	int32 HUDGrenades;
	bool bInitializeGrenades = false;
	float HUDCarriedAmmo;
	bool bInitializeCarriedAmmo = false;
	float HUDWeaponAmmo;
	bool bInitializeWeaponAmo = false;

	float HighPingRunningTime = 0.f;
	
	UPROPERTY(EditAnywhere)
	float HighPingDuration = 5.f;

	float PingAnimationRunningTime = 0.f;
	
	UPROPERTY(EditAnywhere)
	float CheckPingFrequency = 20.f;

	UFUNCTION(Server, Reliable)
	void ServerReportPingStatus(bool bHighPing);
	
	UPROPERTY(EditAnywhere)
	float HighPingThreshold = 50.f;
};
