// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"
#include "FPSCharacter.h"
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
			//MuzzleOffset 을 카메라 스페이스에서 월드 스페이스로 변환
			FVector start = CameraLocation;
			start.Z += 50.0f;
			FVector end = (CameraRotation.Vector()* _traceDistance) + start;
			FHitResult hitResult;
			FCollisionQueryParams collisionParams;
			collisionParams.AddIgnoredActor(this);
			
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
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Hit Actor Name:%s"), *hitActor->GetName()));

				}
			}

		}
	}
}

void AAssaultRifle::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}