// Copyright Rob Kohout


#include "HUD/OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"


void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if(DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::SetDisplayColor(FColor ColorToDisplay)
{
	if(DisplayText)
	{
		FSlateColor DisplayTextColor = FSlateColor(ColorToDisplay);
		DisplayText->SetColorAndOpacity(DisplayTextColor);
	}
}

void UOverheadWidget::ShowPlayerName(APawn* InPawn)
{
	const APlayerState* PlayerState = InPawn->GetPlayerState();
	FString PlayerName = PlayerState ==	nullptr ? "NAME" : PlayerState->GetPlayerName();
	FColor DisplayColor = (InPawn->GetLocalRole() == ENetRole::ROLE_AutonomousProxy ||
							InPawn->GetRemoteRole() == ENetRole::ROLE_AutonomousProxy) ?
								FColor::Blue : FColor::Red;
	SetDisplayText(PlayerName);
	SetDisplayColor(DisplayColor);	
}

void UOverheadWidget::ShowPlayerNetRoles(APawn* InPawn)
{
	FString LocalRole = GetLocalNetRole(InPawn);
	FString RemoteRole = GetRemoteNetRole(InPawn);
	FString DisplayString = FString::Printf(TEXT("Local Role:  %s\nRemote Role:  %s"), *LocalRole, *RemoteRole);
	SetDisplayText(DisplayString);
}

void UOverheadWidget::ShowPlayerLocalNetRole(APawn* InPawn)
{
	FString LocalRole = GetLocalNetRole(InPawn);
	FString DisplayString = FString::Printf(TEXT("Local Role:  %s"), *LocalRole);
	SetDisplayText(DisplayString);
}

void UOverheadWidget::ShowPlayerRemoteNetRole(APawn* InPawn)
{
	FString RemoteRole = GetRemoteNetRole(InPawn);
	FString DisplayString = FString::Printf(TEXT("Remote Role:  %s"), *RemoteRole);
	SetDisplayText(DisplayString);
}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	
	Super::NativeDestruct();
}

FString UOverheadWidget::GetLocalNetRole(APawn* InPawn)
{
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString Role;

	switch(LocalRole)
	{
	case ROLE_Authority:
		Role = FString("Authority");
		break;
	case ROLE_AutonomousProxy:
		Role = FString("AutonomousProxy");
		break;
	case ROLE_SimulatedProxy:
		Role = FString("SimulatedProxy");
		break;
	case ROLE_None:
		Role = FString("None");
		break;
	}
	return Role;
}

FString UOverheadWidget::GetRemoteNetRole(APawn* InPawn)
{
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;
	
	switch(RemoteRole)
	{
	case ROLE_Authority:
		Role = FString("Authority");
		break;
	case ROLE_AutonomousProxy:
		Role = FString("AutonomousProxy");
		break;
	case ROLE_SimulatedProxy:
		Role = FString("SimulatedProxy");
		break;
	case ROLE_None:
		Role = FString("None");
		break;
	}
	return Role;
}
