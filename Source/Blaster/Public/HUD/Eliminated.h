// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Eliminated.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class BLASTER_API UEliminated : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackerNameText;
};
