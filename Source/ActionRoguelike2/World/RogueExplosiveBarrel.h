// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "RogueExplosiveBarrel.generated.h"

UCLASS()
class ACTIONROGUELIKE2_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueExplosiveBarrel();

protected:
	
	UPROPERTY(EditAnywhere, category="Components");
	TObjectPtr<UStaticMeshComponent> BarrelMesh;
	
	UPROPERTY(EditAnywhere, category="Components");
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditAnywhere, category="Components");
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(EditAnywhere, category="Components");
	TObjectPtr<URadialForceComponent> RadialForceComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DmgTypeClass;
	
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
		virtual void PostInitializeComponents() override;
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
};
