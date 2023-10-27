// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SAttributeComponent.h"
#include "SGamePlayFunctionLibrary.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	SphereComp->SetSphereRadius(20.0f);
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorBeginOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnActorHit);
	DamageAmount = 20.0f;
}
/*
void ASMagicProjectile::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		if (USGamePlayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
				// 在命中位置生成粒子特效
				UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
				// 命中产生音效
				USoundBase* Sound = GetImpactSound();
				UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
				EffectComp->DeactivateSystem();
				MovementComp->StopMovementImmediately();
				Explode();
		}
	}
}
*/

void ASMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor && OtherActor != GetInstigator())
	{
			/*if (USGamePlayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, Hit))
			{
				// Only explode when we hit something valid
				ASProjectileBase::Explode();
			}
			*/
			USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
			if (AttributeComp)
			{
				/*
				UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
				// minus in front of DamageAmount to apply the change as damage, not healing
				AttributeComp->ApplyHealthChange(GetInstigator(),-DamageAmount);
				*/
				USGamePlayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, Hit);
				// Only explode when we hit something valid
				ASProjectileBase::Explode();
				
			}
			// 检查是否命中有效的物体（排除投射物自身）
			if (OtherActor && OtherActor != this)
			{
				// 在命中位置生成粒子特效
				UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
				// 命中产生音效
				USoundBase* Sound = GetImpactSound();
				UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
				EffectComp->DeactivateSystem();
				MovementComp->StopMovementImmediately();
			}
			
	}
}
