// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayMagicProjectile.generated.h"


class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class CPPUE5PLAY_API APlayMagicProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APlayMagicProjectile();

protected:
    
    UPROPERTY(VisibleAnywhere, Category = Projectile)
    TObjectPtr<USphereComponent> SphereComp;

    UPROPERTY(VisibleAnywhere, Category = Projectile)
    TObjectPtr<UParticleSystemComponent> EffectComp;

    UPROPERTY(VisibleAnywhere, Category = Projectile)
    TObjectPtr<UProjectileMovementComponent> MovementComp;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
