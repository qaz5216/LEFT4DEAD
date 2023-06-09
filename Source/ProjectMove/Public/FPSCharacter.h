// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
<<<<<<< HEAD
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon.h"
#include "FPSCharacter.generated.h"

=======
#include "FPSCharacter.generated.h"
>>>>>>> 870a3e3f6533c4750aed33d3b5423556b891871d
UCLASS()
class PROJECTMOVE_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

<<<<<<< HEAD
public:
=======
public:	
>>>>>>> 870a3e3f6533c4750aed33d3b5423556b891871d
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
<<<<<<< HEAD
		void MoveForward(float Value);

	// 좌우 이동 처리
	UFUNCTION()
		void MoveRight(float Value);
	//점프
	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();
	//걷기
	UFUNCTION()
		void StartWalk();
	UFUNCTION()
		void StopWalk();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool walking;
	//앉기
	UFUNCTION()
		void StartSitdown();

	UFUNCTION()
		void StopSitdown();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool sitting;
	//발사
	UFUNCTION(BlueprintCallable, Category = "Useable")
		void Fire();
	//발사장탄수 체크
	UFUNCTION()
		void FireCheck();
	UFUNCTION()
		void Interaction();
	UFUNCTION()
		void FireStop();
	//총 스위칭
	UFUNCTION()
		void Switch1();
	UFUNCTION()
		void Switch2();
	UFUNCTION()
		void Switch3();
	//재장전
	UFUNCTION()
		void Reload();
	//공격받았을때
	UFUNCTION(BlueprintCallable, Category = "Useable")
		void Attacked(int32 damage);
	//체력회복
	UFUNCTION(BlueprintCallable, Category = "Useable")
		void Heal();
	//FPS카메라
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* FPSCameraComponent;

	// 일인칭 메시 (오른팔)
	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* RightMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

	// 일인칭 소켓메시
	UPROPERTY(EditAnywhere, Category = Socket)
		USkeletalMeshSocket* SocketMesh;

	// 무기스위치넘버
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Weapon)
		int32 WeaponNum;
	//장탄수
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Weapon)
		int32 Ammo;
	//잔탄수
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Weapon)
		int32 Leftammo;
	//무기
	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* WeaponMesh;
	//총알
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Weapon)
		int32 Weapon1bullet;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		int32 Weapon2bullet;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		int32 Weapon3bullet;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool firing;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		float currentTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		float firetime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		float cameratime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		float shaketime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		float reloadtime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		float linedelaytime; // 라인트레이스 시간
	//카메라흔들지
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool shaking;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool reloading;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		int32 shakingnum;
	//HP
	UPROPERTY(BlueprintReadWrite, Category = Useable)
		int32 HP;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere ,Category = Useable)
		int32 HillPackNum;
	//총기 흔들림
	float lrecoil;
	float rrecoil;
	bool shakeupcamera;
	bool shakedowncamera;
	bool checkcameratime;
	bool sitdowncheck;
	UFUNCTION()
		void ShakeCamerastart();
	UFUNCTION()
		void ShakeCameraend();
	UFUNCTION()
		void Logiccheck();
	UFUNCTION(BlueprintCallable, Category = "Useable")
		bool GetReload();

	//총기클래스
	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category="Weapon",meta=(AllowPrivateAccess="true"))
	TSubclassOf<class AWeapon> _weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Weapon",meta=(AllowPrivateAccess="true"))
	AWeapon* equip_weapon;
	void AttachWeapon(TSubclassOf<class AWeapon> weapon);
	UPROPERTY()
	UAnimationAsset* ReloadAinm;
	FTimerHandle shakehandle;
	//상호작용 물체확인코드 (상호작용가능클래스는 weapon클래스임)
	UFUNCTION()
		bool IsAssaultRifle(AWeapon* HitWeapon);
	UFUNCTION()
		bool IsHealPack(AWeapon* HitWeapon);
	UFUNCTION()
		bool IsAmmoPack(AWeapon* HitWeapon);
	UFUNCTION()
		bool IsElevator(AWeapon* HitWeapon);

	//총구위치
	UPROPERTY(EditAnywhere, Category = Socket)
		UStaticMeshComponent* fireloc;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* EquipSound;
	UPROPERTY(EditDefaultsOnly)
		USoundBase* InteractionSound;
	UPROPERTY(EditDefaultsOnly)
		USoundBase* ReloadSound;
=======
	void MoveForward(float Value);

	// 좌우 이동 처리
	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void StartJump();

	// 좌우 이동 처리
	UFUNCTION()
	void StopJump();

	//FPS카메라
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FPSCameraComponent;

	// 일인칭 메시 (팔), 소유 플레이어에게만 보입니다.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FPSMesh;

>>>>>>> 870a3e3f6533c4750aed33d3b5423556b891871d
};
