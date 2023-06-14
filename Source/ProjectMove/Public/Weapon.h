// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EFireType : uint8
{
	EF_LineTrace UMETA(DisplayName = "Line Trace"),
	EF_Projectile UMETA(DisplayName = "Projectile"),
};


UCLASS(Abstract)
class PROJECTMOVE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	inline int GetAmmoCount() { return _ammoMaxCount; }
	inline float GetReloadingDelayTime() { return _reloadingDelayTime; }
protected:
	//액터의 스태틱메쉬
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* _StaticMeshComponent;
	//탄약최대개수
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	int _ammoMaxCount = 30;
	//현재소지한 탄약의 개수
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	int _ammoRemainCount ;
	//재장전까지 걸리는시간
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	float _reloadingDelayTime = 3.f;
	//발사간의 간격
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	float _fireInteval = 0.1f;
	//LineTrace 의 ray길이
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	float _traceDistance = 10000.f;
	//발사타입
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	EFireType _fireType = EFireType::EF_LineTrace;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	////발사시작
	virtual void StartFire(const class AFPSCharacter* owner) { ; }
	////발사중지
	virtual void StopFire() { ; }

	////재장전
	virtual void Reloading() { ; }
	//// Called every frame
	virtual void FireWithLineTrace(const class AFPSCharacter* owner) { ; }
	virtual void Tick(float DeltaTime) override;
};
