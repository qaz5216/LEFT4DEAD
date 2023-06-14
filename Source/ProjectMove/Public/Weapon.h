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
	//������ ����ƽ�޽�
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* _StaticMeshComponent;
	//ź���ִ밳��
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	int _ammoMaxCount = 30;
	//��������� ź���� ����
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	int _ammoRemainCount ;
	//���������� �ɸ��½ð�
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	float _reloadingDelayTime = 3.f;
	//�߻簣�� ����
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	float _fireInteval = 0.1f;
	//LineTrace �� ray����
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	float _traceDistance = 10000.f;
	//�߻�Ÿ��
	UPROPERTY(EditAnywhere, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"));
	EFireType _fireType = EFireType::EF_LineTrace;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	////�߻����
	virtual void StartFire(const class AFPSCharacter* owner) { ; }
	////�߻�����
	virtual void StopFire() { ; }

	////������
	virtual void Reloading() { ; }
	//// Called every frame
	virtual void FireWithLineTrace(const class AFPSCharacter* owner) { ; }
	virtual void Tick(float DeltaTime) override;
};
