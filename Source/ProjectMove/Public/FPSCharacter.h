// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

};
