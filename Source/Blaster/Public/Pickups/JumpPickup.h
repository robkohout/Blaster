// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "Pickups/Pickup.h"
#include "JumpPickup.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AJumpPickup : public APickup
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
	float JumpZVelocityBuff = 4000.f;

	UPROPERTY(EditAnywhere)
	float JumpBuffTime = 30.f;
};
