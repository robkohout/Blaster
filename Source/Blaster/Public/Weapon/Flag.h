// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "Flag.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AFlag : public AWeapon
{
	GENERATED_BODY()

public:
	AFlag();
	
private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FlagMesh;
};
