// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "Pickups/Pickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AHealthPickup : public APickup
{
	GENERATED_BODY()
	
protected:
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere)
	float HealAmount = 100.f;

	UPROPERTY(EditAnywhere)
	float HealingTime = 5.f;
};
