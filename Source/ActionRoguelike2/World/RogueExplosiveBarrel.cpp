// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueExplosiveBarrel.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetSimulatePhysics(true);
	
	MeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
	RootComponent = MeshComponent;
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(MeshComponent);
	
	RadialForceComp->ImpulseStrength = 150000.0f;
	RadialForceComp->Radius = 750.0f;
	
	RadialForceComp->bAutoActivate = false;
	RadialForceComp->bIgnoreOwningActor = true;
	
}


float ARogueExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (bExploded || GetWorldTimerManager().TimerExists(ExplosionTimerHandle))
	{
		return ActualDamage;
	}
	
	ActiveBurningEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(BurningEffect, MeshComponent, NAME_None,
	FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);

	ActiveBurningSoundComp = UGameplayStatics::SpawnSoundAttached(BurningSound, MeshComponent);
	
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ARogueExplosiveBarrel::Explode, ExplosionDelay);

	return ActualDamage;
}

void ARogueExplosiveBarrel::Explode()
{
	bExploded = true;
	
	ActiveBurningEffectComp->Deactivate();
	ActiveBurningSoundComp->Stop();

	RadialForceComp->FireImpulse();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation(), GetActorRotation());

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
}

