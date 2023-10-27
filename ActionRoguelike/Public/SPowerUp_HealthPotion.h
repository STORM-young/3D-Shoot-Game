// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpActor.h"
#include "Components/StaticMeshComponent.h"
#include "SPowerUp_HealthPotion.generated.h"

/**
 * 
 */

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASPowerUp_HealthPotion : public ASPowerUpActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;
public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

	ASPowerUp_HealthPotion();
};
