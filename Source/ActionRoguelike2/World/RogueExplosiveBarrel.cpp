// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueExplosiveBarrel.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

class UStaticMeshComponent;
class UNiagaraSystem;
class URadialForceComponent;


// Sets default values
ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	RootComponent = BarrelMesh;
	
	ExplosionEffect = CreateDefaultSubobject<UNiagaraSystem>(TEXT("ExplosionEffect"));
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(BarrelMesh);
}

void ARogueExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	BarrelMesh->OnComponentHit.AddDynamic(this, &ARogueExplosiveBarrel::OnActorHit);
	BarrelMesh->SetSimulatePhysics(true);
}

void ARogueExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	
	FVector HitFromDirection = GetActorRotation().Vector();
	
	UGameplayStatics::ApplyPointDamage(this, 10.0f, HitFromDirection, Hit, GetInstigatorController(), OtherActor, DmgTypeClass);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);

	RadialForceComp->FireImpulse();
}


// Called when the game starts or when spawned
//{
//	Super::BeginPlay();
//}

// Called every frame
//void ARogueExplosiveBarrel::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

