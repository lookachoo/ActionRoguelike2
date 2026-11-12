// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "RogueExplosiveBarrel.generated.h"

class URadialForceComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class USoundBase;
class UStaticMeshComponent;


UCLASS()
class ACTIONROGUELIKE2_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueExplosiveBarrel();

protected:
	
	UPROPERTY(EditAnywhere, Category= "Explosive Barrel")
	float ExplosionDelay = 3.0f;
	
	UPROPERTY(EditAnywhere, category="Explosive Barrel");
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditAnywhere, category="Explosive Barrel");
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(EditAnywhere, category="Explosive Barrel");
	TObjectPtr<UNiagaraSystem> BurningEffect;
	
	UPROPERTY(EditAnywhere, category="Explosive Barrel");
	TObjectPtr<USoundBase> BurningSound;
		
	UPROPERTY(EditAnywhere, category="Explosive Barrel");
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditAnywhere, category="Explosive Barrel");
	TObjectPtr<URadialForceComponent> RadialForceComp;
	
	void Explode();
	
	bool bExploded = false;
	
	FTimerHandle ExplosionTimerHandle;
	
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningEffectComp = nullptr;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveBurningSoundComp = nullptr;
	
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
};
