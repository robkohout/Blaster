// Copyright Rob Kohout


#include "Weapon/ProjectileRocket.h"

#include "Kismet/GameplayStatics.h"

AProjectileRocket::AProjectileRocket()
{
	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));
	RocketMesh->SetupAttachment(RootComponent);
	RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AProjectileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	if (APawn* FiringPawn = GetInstigator())
	{
		if (AController* FiringController = FiringPawn->GetController())
		{
			UGameplayStatics::ApplyRadialDamageWithFalloff(
				this, // world context object
				Damage, // base damage
				10.f, // minimum damage
				GetActorLocation(), // origin
				200.f, // inner radius
				500.f, // outer radius
				1.f, // damage falloff
				UDamageType::StaticClass(), // damage type class
				TArray<AActor*>(), // ignore actors
				this, // damage causer
				FiringController // instigator controller
				);			
		}
	}
	
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
