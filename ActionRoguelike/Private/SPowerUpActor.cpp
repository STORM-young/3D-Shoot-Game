// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"
#include "Components/SphereComponent.h"

// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    SphereComp->SetCollisionProfileName("PowerUp");
    RootComponent = SphereComp;

    RespawnTime = 10.0f;
}

void ASPowerUpActor::ShowPowerup()
{
    SetPowerupState(true);
}

void ASPowerUpActor::HideAndCooldownPowerup()
{
    SetPowerupState(false);
    GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPowerUpActor::ShowPowerup, RespawnTime);
}

void ASPowerUpActor::SetPowerupState(bool bNewIsActive)
{
    SetActorEnableCollision(bNewIsActive);

    //set visibility on root and all children
    RootComponent->SetVisibility(bNewIsActive, true);
}

void ASPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{
    // logic in derived class
}

