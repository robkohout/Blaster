// Copyright Rob Kohout

#include "Weapon/Casing.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ACasing::ACasing()
{
 	PrimaryActorTick.bCanEverTick = false;

	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasingMesh"));
	SetRootComponent(CasingMesh);
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetEnableGravity(true);
	CasingMesh->SetNotifyRigidBodyCollision(true);
	ShellEjectionImpulse = 10.f;
}

void ACasing::BeginPlay()
{
	Super::BeginPlay();
	
	CasingMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	CasingMesh->AddImpulse(GetActorForwardVector() * ShellEjectionImpulse);
}

void ACasing::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ShellSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}
	SetLifeSpan(0.1f);
}
