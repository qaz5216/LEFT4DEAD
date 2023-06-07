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


	// 일인칭 카메라 컴포넌트를 생성합니다.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// 카메라 컴포넌트를 캡슐 컴포넌트에 붙입니다.
	FPSCameraComponent->SetupAttachment(RootComponent);
	// 카메라 위치를 눈 살짝 위쪽으로 잡습니다.
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    // 폰의 로테이션 제어를 허가합니다.
    FPSCameraComponent->bUsePawnControlRotation = true;
	
	// 일인칭 메시 컴포넌트입니다.
	LeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftMesh"));
	// 소유 플레이어만 이 메시를 볼 수 있습니다.
	LeftMesh->SetOnlyOwnerSee(true);
	// FPS 메시를 FPS 카메라에 붙입니다.
	LeftMesh->SetupAttachment(FPSCameraComponent);
	// 일부 환경 섀도잉을 꺼 메시가 하나인 듯 보이는 느낌을 유지합니다.
	LeftMesh->bCastDynamicShadow = false;
	LeftMesh->CastShadow = false;

	RightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightMesh"));
	// 소유 플레이어만 이 메시를 볼 수 있습니다.
	RightMesh->SetOnlyOwnerSee(true);
	// FPS 메시를 FPS 카메라에 붙입니다.
	RightMesh->SetupAttachment(FPSCameraComponent);
	// 일부 환경 섀도잉을 꺼 메시가 하나인 듯 보이는 느낌을 유지합니다.
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
		// 5 초간 디버그 메시지를 표시합니다. (첫 인수인) -1 "Key" 값은 이 메시지를 업데이트 또는 새로고칠 필요가 없음을 나타냅니다.
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

	//Move바인딩 구성
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	
	//Look바인딩 구성
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);
	
	//"action"바인딩 구성
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

void AFPSCharacter::MoveForward(float Value)
{
	//어느쪽이 전방인지 알아내어 플레이어가 그방향으로 이동하고자 한다고 기록합니다.
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
		//카메라 트랜스폼 구하기
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		//MuzzleOffset 을 카메라 스페이스에서 월드 스페이스로 변환
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		//조준을 약간 윗쪽으로 올려줍니다.
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		UE_LOG(LogTemp, Log, TEXT("Hello"));
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			// 총구 위치에 발사체를 스폰시킵니다.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				//발사방향 알아내기
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
				// 총알수명 3초로 정해주기
				Projectile->SetLifeSpan(3.0f);
			}
		}
	}
}