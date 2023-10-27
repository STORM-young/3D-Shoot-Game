// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;
      
UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();
protected:
	/* VisibleAnywhere = read-only, still useful to view in-editor and enforce a convention. */
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HandSocketName;

	UPROPERTY(visibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(visibleAnywhere)
	UCameraComponent *CameraComp;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* BlackHoleAttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* TeleportAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float BlackHoleAttackAnimDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float RisingAnimDelay;

	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;

	/* Particle System played during attack animation */
	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* CastingEffect;

	//UPROPERTY(EditAnywhere, Category= "Attack")
	//UAnimMontage* FireAnim;

	UPROPERTY(visibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	USAttributeComponent* AttributeComp;

	FTimerHandle TimerHandle_BlackholeAttack;
	FTimerHandle TimerHandle_Dash;
	FTimerHandle TimerHandle_DashAnim;
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Rising;
	void PrimaryAttack_TimeElapsed();
	
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MoveForward(float value);
	void MoveRight(float value);
	void PrimaryAttack();
	void PrimaryInteract();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	void BlackHoleAttack();
	void BlackholeAttack_TimeElapsed();
	void StartFalling();
	void Dash();
	void Dash_TimeElapsed();
	void Dash_AnimPlay();
	void StartAttackEffects();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,USAttributeComponent* OwningComp,float NewHealth,float Delta);
	//void Tick(float DeltaTime);
	virtual void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;

	UFUNCTION(Exec)
	void HealSelf(float amount=100);
};
