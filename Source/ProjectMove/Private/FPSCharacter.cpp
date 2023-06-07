// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "FPSProjectile.h"
#include "GameFramework/Character.h"
// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// ����Ī ī�޶� ������Ʈ�� �����մϴ�.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// ī�޶� ������Ʈ�� ĸ�� ������Ʈ�� ���Դϴ�.
	FPSCameraComponent->SetupAttachment(RootComponent);
	// ī�޶� ��ġ�� �� ��¦ �������� ����ϴ�.
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    // ���� �����̼� ��� �㰡�մϴ�.
    FPSCameraComponent->bUsePawnControlRotation = true;
	
	// ����Ī �޽� ������Ʈ�Դϴ�.
	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftMesh"));
	// ���� �÷��̾ �� �޽ø� �� �� �ֽ��ϴ�.
	LeftMesh->SetOnlyOwnerSee(true);
	// FPS �޽ø� FPS ī�޶� ���Դϴ�.
	LeftMesh->SetupAttachment(FPSCameraComponent);
	// �Ϻ� ȯ�� �������� �� �޽ð� �ϳ��� �� ���̴� ������ �����մϴ�.
	LeftMesh->bCastDynamicShadow = false;
	LeftMesh->CastShadow = false;

	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightMesh"));
	// ���� �÷��̾ �� �޽ø� �� �� �ֽ��ϴ�.
	RightMesh->SetOnlyOwnerSee(true);
	// FPS �޽ø� FPS ī�޶� ���Դϴ�.
	RightMesh->SetupAttachment(FPSCameraComponent);
	// �Ϻ� ȯ�� �������� �� �޽ð� �ϳ��� �� ���̴� ������ �����մϴ�.
	RightMesh->bCastDynamicShadow = false;
	RightMesh->CastShadow = false;
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// 5 �ʰ� ����� �޽����� ǥ���մϴ�. (ù �μ���) -1 "Key" ���� �� �޽����� ������Ʈ �Ǵ� ���ΰ�ĥ �ʿ䰡 ������ ��Ÿ���ϴ�.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Move���ε� ����
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	
	//Look���ε� ����
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);
	
	//"action"���ε� ����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForward(float Value)
{
	//������� �������� �˾Ƴ��� �÷��̾ �׹������� �̵��ϰ��� �Ѵٰ� ����մϴ�.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	UE_LOG(LogTemp, Log, TEXT("Hi"));
	if (ProjectileClass)
	{
		//ī�޶� Ʈ������ ���ϱ�
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		//MuzzleOffset �� ī�޶� �����̽����� ���� �����̽��� ��ȯ
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		//������ �ణ �������� �÷��ݴϴ�.
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		UE_LOG(LogTemp, Log, TEXT("Hello"));
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			// �ѱ� ��ġ�� �߻�ü�� ������ŵ�ϴ�.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				//�߻���� �˾Ƴ���
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
				// �Ѿ˼��� 3�ʷ� �����ֱ�
				Projectile->SetLifeSpan(3.0f);
			}
		}
	}
}