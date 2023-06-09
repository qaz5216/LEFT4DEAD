// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "AssaultRifle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMOVE_API AAssaultRifle : public AWeapon
{
	GENERATED_BODY()
	private:
		FTimerHandle FireTimerHandle;

	public:
		virtual void StartFire(class AFPSCharacter* owner);
		////발사중지
		virtual void StopFire();

		////재장전
		virtual void Reloading(class AFPSCharacter* owner);
		//// Called every frame
		virtual void FireWithLineTrace(class AFPSCharacter* owner);
		
		UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

		UPROPERTY(EditDefaultsOnly, Category="Explosion")
		class UParticleSystem* explosionFactory;

		UPROPERTY(EditDefaultsOnly)
		USoundBase* FireSound;
};
