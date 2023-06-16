// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon.h"
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

	// �¿� �̵� ó��
	UFUNCTION()
		void MoveRight(float Value);
	//����
	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();
	//�ȱ�
	UFUNCTION()
		void StartWalk();
	UFUNCTION()
		void StopWalk();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool walking;
	//�ɱ�
	UFUNCTION()
		void StartSitdown();

	UFUNCTION()
		void StopSitdown();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool sitting;
	//�߻�
	UFUNCTION(BlueprintCallable, Category = "Useable")
		void Fire();
	//�߻���ź�� üũ
	UFUNCTION()
		void FireCheck();
	UFUNCTION()
		void FireStop();
	//�� ����Ī
	UFUNCTION()
		void Switch1();
	UFUNCTION()
		void Switch2();
	UFUNCTION()
		void Switch3();
	//������
	UFUNCTION()
		void Reload();
	//���ݹ޾�����
	UFUNCTION(BlueprintCallable, Category = "Useable")
		void Attacked(int32 damage);
	//ü��ȸ��
	UFUNCTION(BlueprintCallable, Category = "Useable")
		void Heal(int32 healing);
	//FPSī�޶�
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* FPSCameraComponent;

	// ����Ī �޽� (������)
	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* RightMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

	// ����Ī ���ϸ޽�
	UPROPERTY(EditAnywhere, Category = Socket)
		USkeletalMeshSocket* SocketMesh;

	// ���⽺��ġ�ѹ�
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Weapon)
		int32 WeaponNum;
	//��ź��
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Weapon)
		int32 Ammo;
	//��ź��
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = Weapon)
		int32 Leftammo;
	//����
	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* WeaponMesh;
	//�Ѿ�
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
	//ī�޶������
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool shaking;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		bool reloading;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Weapon)
		int32 shakingnum;
	//HP
	UPROPERTY(BlueprintReadWrite, Category = Useable)
		int32 HP;
	//�ѱ� ��鸲
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

	//�ѱ�Ŭ����
	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category="Weapon",meta=(AllowPrivateAccess="true"))
	TSubclassOf<class AWeapon> _weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Weapon",meta=(AllowPrivateAccess="true"))
	AWeapon* equip_weapon;
	void AttachWeapon(TSubclassOf<class AWeapon> weapon);
	UPROPERTY()
	UAnimationAsset* ReloadAinm;
};
