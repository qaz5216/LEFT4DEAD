// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"
#include "FPSCharacter.h"
#include "FPSProjectile.h"
void AAssaultRifle::StartFire(const AFPSCharacter* owner)
{
	if (owner)
	{
		switch(_fireType)
		{
			case EFireType::EF_LineTrace:
				GetWorldTimerManager().SetTimer(
					FireTimerHandle,
					[owner, this]() {FireWithLineTrace(owner); },
					_fireInteval,
					true);
			break;
			case EFireType::EF_Projectile:
			break;
		}
	}
}

void AAssaultRifle::FireWithLineTrace(const class AFPSCharacter* owner)
{
	if (_ammoRemainCount < 0)
	{
		StopFire();
	}
	if (owner)
	{
		const AController* ownerController = owner->GetController();

		if (ownerController) 
		{
			FVector CameraLocation;
			FRotator CameraRotation;
			owner->GetActorEyesViewPoint(CameraLocation, CameraRotation);
			//MuzzleOffset �� ī�޶� �����̽����� ���� �����̽��� ��ȯ
			FVector start = CameraLocation;
			start.Z += 50.0f;
			FVector end = (CameraRotation.Vector()* _traceDistance) + start;
			FHitResult hitResult;
			FCollisionQueryParams collisionParams;
			collisionParams.AddIgnoredActor(this);
			//���������� Ȯ�ο�
			DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1.0f);
			if (GetWorld()->LineTraceSingleByChannel(
				hitResult,
				start,
				end,
				ECC_Visibility,
				collisionParams))
			{
				if (hitResult.GetActor())
				{
					auto* hitActor = hitResult.GetActor();
					//�����¾Ҵ��� Ȯ�ο�
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Hit Actor Name:%s"), *hitActor->GetName()));
					FVector projectiledirection = hitResult.Location - owner->RightMesh->GetSocketLocation("WeaponSocket");
					UWorld* world = GetWorld();
					if (world)
					{
						FActorSpawnParameters SpawnParams;
						SpawnParams.Owner = this;
						SpawnParams.Instigator = GetInstigator();
						AFPSProjectile* projectile = world->SpawnActor<AFPSProjectile>(ProjectileClass, owner->RightMesh->GetSocketLocation("WeaponSocket"), CameraRotation, SpawnParams);
						if (projectile)
						{	

							
								//�Ѿ� �����ġ����
							projectile->SetActorLocation(owner->RightMesh->GetSocketLocation("WeaponSocket"));
							if (projectiledirection.Normalize())
							{
								projectile->FireInDirection(projectiledirection);
								projectile->SetLifeSpan(3.0f);
								projectile->ProjectileMovementComponent->InitialSpeed = 3000.0f;
								projectile->ProjectileMovementComponent->MaxSpeed = 3000.0f;
								_ammoRemainCount--;
								GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("remain%d"),_ammoRemainCount));
							}
						}
					}

				}
			}

		}
	}
}

void AAssaultRifle::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}