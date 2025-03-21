﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
APlayMagicProjectile::APlayMagicProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    SphereComp->SetCollisionProfileName("Projectile");
    RootComponent = SphereComp;
    
    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
    EffectComp->SetupAttachment(SphereComp);
    
    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
    MovementComp->InitialSpeed = 1000.0f;
    MovementComp->bRotationFollowsVelocity = true;
    MovementComp->bInitialVelocityInLocalSpace = true;
    
}

// Called when the game starts or when spawned
void APlayMagicProjectile::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void APlayMagicProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

