// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/SkeletalMeshSocket.h"
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

	//�߻�
	UFUNCTION()
		void Fire();
	//�߻���ź�� üũ
	UFUNCTION()
		void FireCheck();

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

	// ����Ī �޽� (����)
	UPROPERTY(EditAnywhere, Category = Mesh)
		USkeletalMeshComponent* LeftMesh;
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
	UPROPERTY(EditAnywhere, Category = Weapon)
		int32 WeaponNum;
	//����
	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* WeaponMesh;
	//�Ѿ�
	UPROPERTY(EditAnywhere, Category = Weapon)
		int32 Weapon1bullet;
	UPROPERTY(EditAnywhere, Category = Weapon)
		int32 Weapon2bullet;
	UPROPERTY(EditAnywhere, Category = Weapon)
		int32 Weapon3bullet;
	//HP
	UPROPERTY(BlueprintReadWrite, Category = Useable)
		int32 HP;
};
