﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;


UCLASS()
class CPPUE5PLAY_API APlayExplosiveBarrel : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APlayExplosiveBarrel();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;

    UPROPERTY(VisibleAnywhere)
    URadialForceComponent* ForceComp;

    virtual void PostInitializeComponents() override;

    // Must be marked with ufunction in order to 'bind' the event
    UFUNCTION()
    void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
