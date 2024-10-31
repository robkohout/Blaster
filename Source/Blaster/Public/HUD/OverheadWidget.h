// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"


/**
 * 
 */
UCLASS()
class BLASTER_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayText;

	UFUNCTION(BlueprintCallable)
	void SetDisplayText(FString TextToDisplay);

	UFUNCTION(BlueprintCallable)
	void SetDisplayColor(FColor ColorToDisplay);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerName(APawn* InPawn);
	
	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRoles(APawn* InPawn);
	
	UFUNCTION(BlueprintCallable)
	void ShowPlayerLocalNetRole(APawn* InPawn);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerRemoteNetRole(APawn* InPawn);
	
protected:
	virtual void NativeDestruct() override;

	FString GetLocalNetRole(APawn* InPawn);
	FString GetRemoteNetRole(APawn* InPawn);
};
