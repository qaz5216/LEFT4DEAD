// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"
#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include <Kismet/GameplayStatics.h>
void AAssaultRifle::StartFire(AFPSCharacter* owner)
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

void AAssaultRifle::FireWithLineTrace(class AFPSCharacter* owner)
{
	if (_ammoRemainCount <= 0)
	{
		StopFire();
	}
	else if (owner)
	{
		const AController* ownerController = owner->GetController();

		if (ownerController) 
		{
			FVector CameraLocation;
			FRotator CameraRotation;
			owner->GetActorEyesViewPoint(CameraLocation, CameraRotation);
			//MuzzleOffset 을 카메라 스페이스에서 월드 스페이스로 변환
			FVector start = CameraLocation;
			start.Z -= 18.5f;
			FVector end = (CameraRotation.Vector()* _traceDistance) + start;
			FHitResult hitResult;
			FCollisionQueryParams collisionParams;
			collisionParams.AddIgnoredActor(this);
			//빨강선으로 확인용
			//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1.0f);
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
					//뭐에맞았는지 확인용
					//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Hit Actor Name:%s"), *hitActor->GetName()));
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
								//총알 출발위치생성
							projectile->SetActorLocation(owner->RightMesh->GetSocketLocation("WeaponSocket"));
							if (projectiledirection.Normalize())
							{
								projectiledirection.Normalize();
								UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, owner->RightMesh->GetSocketLocation("WeaponSocket") + projectiledirection * 60,FRotator(),FVector(1,1,1));
								projectile->FireInDirection(projectiledirection);
								projectile->SetLifeSpan(3.0f);
								projectile->ProjectileMovementComponent->InitialSpeed = 3000.0f;
								projectile->ProjectileMovementComponent->MaxSpeed = 3000.0f;
								_ammoRemainCount--;
								owner->Leftammo = _ammoRemainCount;
								owner->ShakeCamerastart();
								//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("remain%d"),_ammoRemainCount));
							}
						}
					}

				}
			}
			else { // 맞은게 없으면
				FVector projectiledirection = end - owner->RightMesh->GetSocketLocation("WeaponSocket");
				UWorld* world = GetWorld();
				if (world)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = GetInstigator();
					AFPSProjectile* projectile = world->SpawnActor<AFPSProjectile>(ProjectileClass, owner->RightMesh->GetSocketLocation("WeaponSocket"), CameraRotation, SpawnParams);
					if (projectile)
					{
						//총알 출발위치생성
						projectile->SetActorLocation(owner->RightMesh->GetSocketLocation("WeaponSocket"));
						if (projectiledirection.Normalize())
						{
							projectile->FireInDirection(projectiledirection);
							projectile->SetLifeSpan(3.0f);
							projectile->ProjectileMovementComponent->InitialSpeed = 3000.0f;
							projectile->ProjectileMovementComponent->MaxSpeed = 3000.0f;
							_ammoRemainCount--;
							owner->Leftammo = _ammoRemainCount;
							owner->ShakeCamerastart();
							//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("remain%d"), _ammoRemainCount));
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

void AAssaultRifle::Reloading(class AFPSCharacter* owner)
{
	if (owner->Weapon1bullet>=30)
	{
		if (_ammoRemainCount == 0)
		{

			_ammoRemainCount = 30;
			owner->Leftammo = _ammoRemainCount;
			owner->Weapon1bullet -= 30;
		}
		else {
			owner->Weapon1bullet += _ammoRemainCount;
			_ammoRemainCount = 30;
			owner->Leftammo = _ammoRemainCount;
			owner->Weapon1bullet -= 30;
		}
		
	}
	else {
		if (_ammoRemainCount == 0)
		{
			_ammoRemainCount = owner->Weapon1bullet;
			owner->Leftammo = _ammoRemainCount;
			owner->Weapon1bullet = 0;
		}
		else {
			if (_ammoRemainCount + owner->Weapon1bullet >= 30)
			{
				owner->Weapon1bullet += _ammoRemainCount;
				_ammoRemainCount = 30;
				owner->Leftammo = _ammoRemainCount;
				owner->Weapon1bullet -= 30;
			}
			else
			{
				_ammoRemainCount += owner->Weapon1bullet;
				owner->Leftammo = _ammoRemainCount;
				owner->Weapon1bullet = 0;
			}
		}
	}
}
