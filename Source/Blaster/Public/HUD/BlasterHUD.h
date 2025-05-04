// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"

class UElimAnnouncement;
class UEliminated;
class UAnnouncement;
class UCharacterOverlay;

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()

public:
	UTexture2D* CrosshairsCenter;
	UTexture2D* CrosshairsLeft;
	UTexture2D* CrosshairsRight;
	UTexture2D* CrosshairsTop;
	UTexture2D* CrosshairsBottom;
	float CrosshairSpread;
	FLinearColor CrosshairsColor;
};

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
	void AddCharacterOverlay();
	
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<UUserWidget> CharacterOverlayClass;

	UPROPERTY()
	UCharacterOverlay* CharacterOverlay = nullptr;

	UPROPERTY(EditAnywhere, Category = "Announcements")
	TSubclassOf<UUserWidget> AnnouncementClass;

	UPROPERTY()
	UAnnouncement* Announcement;

	void AddAnnouncement();

	UPROPERTY(EditAnywhere, Category = "Eliminated")
	TSubclassOf<UUserWidget> EliminatedClass;

	UPROPERTY()
	UEliminated* Eliminated;

	void AddEliminated();

	void AddElimAnnouncement(FString Attacker, FString Victim);
	
protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY()
	APlayerController* OwningPlayer;
	
	FHUDPackage HUDPackage;

	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportCenter, FVector2D Spread, FLinearColor CrosshairColor);

	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 16.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UElimAnnouncement> ElimAnnouncementClass;
	
public:
	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) { HUDPackage = Package; }
};
