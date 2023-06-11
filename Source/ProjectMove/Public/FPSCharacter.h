// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/SkeletalMeshSocket.h"
//#include "Camera/CameraShake.h"
#include "FPSCharacter.generated.h"

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
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
		void Heal(int32 healing);
	//FPS카메라
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* FPSCameraComponent;

	// 일인칭 메시 (왼팔)
	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* LeftMesh;
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
	//카메라흔들지
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool shaking;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		int32 shakingnum;
	//HP
	UPROPERTY(BlueprintReadWrite, Category = Useable)
		int32 HP;
	//총기 흔들림
	float lrecoil;
	float rrecoil;
	bool shakeupcamera;
	bool shakedowncamera;
	UFUNCTION()
		void ShakeCamerastart();
	UFUNCTION()
		void ShakeCameraend();
};
