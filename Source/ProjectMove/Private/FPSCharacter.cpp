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
	// ���ϸ޽� �Դϴ�.
	SocketMesh = CreateDefaultSubobject<USkeletalMeshSocket>(TEXT("SocketMesh"));
	// ����Ī �޽� ������Ʈ�Դϴ�.
	LeftMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftMesh"));
	// ���� �÷��̾ �� �޽ø� �� �� �ֽ��ϴ�.
	LeftMesh->SetOnlyOwnerSee(true);
	// FPS �޽ø� FPS ī�޶� ���Դϴ�.
	LeftMesh->SetupAttachment(FPSCameraComponent);
	// �Ϻ� ȯ�� �������� �� �޽ð� �ϳ��� �� ���̴� ������ �����մϴ�.
	LeftMesh->bCastDynamicShadow = false;
	LeftMesh->CastShadow = false;
	LeftMesh->SetRelativeLocation(FVector(75.0f, -10.0f, -60.0f));
	LeftMesh->SetRelativeRotation(FRotator(0.0,50.0,0.0));
	RightMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightMesh"));
	//RightMesh->SkeletalMesh->AddSocket(SocketMesh);
	// ���� �÷��̾ �� �޽ø� �� �� �ֽ��ϴ�.
	RightMesh->SetOnlyOwnerSee(true);
	// FPS �޽ø� FPS ī�޶� ���Դϴ�.
	RightMesh->SetupAttachment(FPSCameraComponent);
	// �Ϻ� ȯ�� �������� �� �޽ð� �ϳ��� �� ���̴� ������ �����մϴ�.
	RightMesh->bCastDynamicShadow = false;
	RightMesh->CastShadow = false;
	GetMesh()->SetOwnerNoSee(true);
	RightMesh->SetRelativeLocation(FVector(90.0f, 40.0f, -60.0f));
	RightMesh->SetRelativeRotation(FRotator(0.0, -10.0, 0.0));
	
	//ó�� ���� 1
	WeaponNum = 1;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RightMesh);
	WeaponMesh->bCastDynamicShadow = false;
	WeaponMesh->CastShadow = false;
	WeaponMesh->SetRelativeLocation(FVector(90.0f, 40.0f, 100.0f));
	Ammo = 30;
	Leftammo = 30;
	Weapon1bullet = 30;
	Weapon2bullet = 10;
	Weapon3bullet = 3;
	HP = 100;
	firing = false;
	currentTime = 0;
	firetime = 0.2f;
	shakeupcamera = false;
	shakedowncamera = false;
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
	if (firing) {
		currentTime += DeltaTime;
		if (currentTime >= firetime) {
			if (Weapon1bullet > 0) {
				Fire();
			}
			currentTime = 0;
		}
	}
	cameratime += DeltaTime;
	shaketime += DeltaTime;
	if (shaking) {
		if (shakingnum % 2 == 0)
		{
			LeftMesh->SetRelativeLocation(FVector(75.0f-(10.0f*((shaketime - lrecoil) / 0.05f)), -10.0f, -60.0f));
			RightMesh->SetRelativeLocation(FVector(90.0f-(10.0f * ((shaketime - lrecoil) / 0.05f)), 40.0f, -60.0f));
			AddControllerPitchInput(-0.6f * ((shaketime - lrecoil) / 0.05f));
			lrecoil = shaketime;
		}
		else
		{
			LeftMesh->SetRelativeLocation(FVector(65.0f+(10.0f * ((shaketime - rrecoil) / 0.05f)), -10.0f, -60.0f));
			RightMesh->SetRelativeLocation(FVector(80.0f + (10.0f * ((shaketime - rrecoil) / 0.05f)), 40.0f, -60.0f));
			AddControllerPitchInput(0.6f * ((shaketime - rrecoil) / 0.05f));
			rrecoil = shaketime;
		}
		if (shaketime >= 0.05f) {
			shaketime = 0;
			shakingnum++;
			if (shakingnum == 2)
				shaking = false;
		}
	}

	if (shakeupcamera) {
		if (cameratime <= 0.1) {
			if (WeaponNum == 1) {
				LeftMesh->SetRelativeRotation(FRotator(2.0 * (cameratime / 0.1f), 50.0, 0.0));
				RightMesh->SetRelativeRotation(FRotator(2.0 * (cameratime / 0.1f), -10.0, 0.0));
			}
			else {
				LeftMesh->SetRelativeRotation(FRotator(30.0 * (cameratime / 0.1f), 50.0, 0.0));
				RightMesh->SetRelativeRotation(FRotator(30.0 * (cameratime / 0.1f), -10.0, 0.0));
			}
		}
	}
	/*if (shakedowncamera) {
		if (cameratime >= 0.1) {
			if (WeaponNum == 1) {
				LeftMesh->SetRelativeRotation(FRotator(10-10.0 * (cameratime / 0.1f), 50.0, 0.0));
				RightMesh->SetRelativeRotation(FRotator(10-10.0 * (cameratime / 0.1f), -10.0, 0.0));
			}
			else {
				LeftMesh->SetRelativeRotation(FRotator(30-30.0 * (cameratime / 0.1f), 50.0, 0.0));
				RightMesh->SetRelativeRotation(FRotator(30-30.0 * (cameratime / 0.1f), -10.0, 0.0));
			}
		}
	}*/
		if (cameratime >= 0.3f) {
			shakedowncamera = false;
			shakeupcamera = false;
			cameratime = 0;
			ShakeCameraend();
		}
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
	//�ȱ�
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AFPSCharacter::StartWalk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &AFPSCharacter::StopWalk);
	//��ũ����
	PlayerInputComponent->BindAction("Sitdown", IE_Pressed, this, &AFPSCharacter::StartSitdown);
	PlayerInputComponent->BindAction("Sitdown", IE_Released, this, &AFPSCharacter::StopSitdown);

	//�߻�
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::FireCheck);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::FireStop);
	//�ѽ���Ī
	PlayerInputComponent->BindAction("Switch1", IE_Pressed, this, &AFPSCharacter::Switch1);
	PlayerInputComponent->BindAction("Switch2", IE_Pressed, this, &AFPSCharacter::Switch2);
	PlayerInputComponent->BindAction("Switch3", IE_Pressed, this, &AFPSCharacter::Switch3);
	//������
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPSCharacter::Reload);
}

void AFPSCharacter::MoveForward(float Value)
{
	//������� �������� �˾Ƴ��� �÷��̾ �׹������� �̵��ϰ��� �Ѵٰ� ����մϴ�.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	if (walking)
	{
		AddMovementInput(Direction*0.5, Value);
	}
	else
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	if (walking)
	{
		AddMovementInput(Direction * 0.5, Value);
	}
	else
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
	
	if (ProjectileClass)
	{
		//ī�޶� Ʈ������ ���ϱ�

		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		//MuzzleOffset �� ī�޶� �����̽����� ���� �����̽��� ��ȯ
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		//������ �ణ �������� �÷��ݴϴ�.//�ȿø�
		MuzzleRotation.Pitch += 0.0f;
		// �Ѿ� �߻縦 ���� �� �ø�
		MuzzleLocation.Z += 50.0f;
		UWorld* World = GetWorld();
		//ī�޶� ����ũ
		ShakeCamerastart();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			// �ѱ� ��ġ�� �߻�ü�� ������ŵ�ϴ�.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{	
				//�ѿ� ���� �߻�
				if (WeaponNum == 1) {
					//�߻���� �˾Ƴ���
					FVector LaunchDirection = MuzzleRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);
					// �Ѿ˼��� 3�ʷ� �����ֱ�
					Projectile->SetLifeSpan(3.0f);
					Projectile->ProjectileMovementComponent->InitialSpeed = 30000.0f;
					Projectile->ProjectileMovementComponent->MaxSpeed = 30000.0f;
					Weapon1bullet--;
					Leftammo = Weapon1bullet;
					UE_LOG(LogTemp, Log, TEXT("%d"), Weapon1bullet);
				}
				else if(WeaponNum == 2) {
					//�߻���� �˾Ƴ���
					FVector LaunchDirection = MuzzleRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);
					// �Ѿ˼��� 3�ʷ� �����ֱ�
					Projectile->SetLifeSpan(3.0f);
					Projectile->ProjectileMovementComponent->InitialSpeed = 3000.0f;
					Projectile->ProjectileMovementComponent->MaxSpeed = 3000.0f;
					Weapon2bullet--;

					Leftammo = Weapon2bullet;
					UE_LOG(LogTemp, Log, TEXT("%d"), Weapon2bullet);
				}
				else if(WeaponNum == 3) {
					//�߻���� �˾Ƴ���
					FVector LaunchDirection = MuzzleRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);
					// �Ѿ˼��� 3�ʷ� �����ֱ�
					Projectile->SetLifeSpan(3.0f);
					Projectile->ProjectileMovementComponent->InitialSpeed = 300.0f;
					Projectile->ProjectileMovementComponent->MaxSpeed = 300.0f;
					Weapon3bullet--;

					Leftammo = Weapon3bullet;
					UE_LOG(LogTemp, Log, TEXT("%d"), Weapon3bullet);
				}
			}
		}
	}
}

void AFPSCharacter::Switch1()
{
	if (WeaponNum != 1) 
	{
		WeaponNum = 1;
		WeaponMesh->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
		WeaponMesh->SetRelativeLocation(FVector(90.0f, 40.0f, 100.0f));
		Ammo = 30;
		Leftammo = Weapon1bullet;
	}
}
void AFPSCharacter::Switch2()
{
	firing = false; //���� �������·� ����Ī�ϴ°�� ����
	if (WeaponNum != 2)
	{
		WeaponNum = 2;
		WeaponMesh->SetRelativeScale3D(FVector(0.5f, 1.0f, 1.0f));
		WeaponMesh->SetRelativeLocation(FVector(70.0f, 40.0f, 100.0f));
		Ammo = 10;
		Leftammo = Weapon2bullet;
	}
}
void AFPSCharacter::Switch3()
{
	firing = false; //���� �������·� ����Ī�ϴ°�� ����
	if (WeaponNum != 3)
	{
		WeaponNum = 3;
		WeaponMesh->SetRelativeScale3D(FVector(0.25f, 1.0f, 1.0f));
		WeaponMesh->SetRelativeLocation(FVector(60.0f, 40.0f, 100.0f));
		Ammo = 3;
		Leftammo = Weapon3bullet;
	}

}
void AFPSCharacter::Reload()
{
	if (WeaponNum == 1)
	{
		Weapon1bullet = 30;
		Leftammo = Weapon1bullet;
	}
	else if (WeaponNum == 2)
	{
		Weapon2bullet = 10;
		Leftammo = Weapon2bullet;
	}
	else if (WeaponNum == 3)
	{
		Weapon3bullet = 3;
		Leftammo = Weapon3bullet;
	}
}

void AFPSCharacter::FireCheck()
{
	UE_LOG(LogTemp, Log, TEXT("Action"));
	if (WeaponNum == 1)
	{
		firing = true;
		if (Weapon1bullet>0)
			Fire();
		UE_LOG(LogTemp, Log, TEXT("firing=%d"),firing);
	}
	else if (WeaponNum == 2)
	{
		if (Weapon2bullet > 0)
			Fire();
		else {
			UE_LOG(LogTemp, Log, TEXT("Reload plz"));
		}
	}
	else if (WeaponNum == 3)
	{
		if (Weapon3bullet > 0)
			Fire();
		else {
			UE_LOG(LogTemp, Log, TEXT("Reload plz"));
		}
	}
}
void AFPSCharacter::Attacked(int32 damage)
{
	if (HP - damage <= 0)
		HP = 0;
	else {
		HP -= damage;
	}
}

void AFPSCharacter::Heal(int32 healing)
{
	if (HP + healing >= 100)
		HP = 100;
	else {
		HP += healing;
	}
}

void AFPSCharacter::FireStop()
{
	if (WeaponNum == 1) {
		firing = false;
		UE_LOG(LogTemp, Log, TEXT("firing=%d"), firing);
		currentTime = 0;
	}
}


void AFPSCharacter::ShakeCamerastart()
{
	shakingnum = 0;
	cameratime = 0;
	/*if (WeaponNum == 1) {
		LeftMesh->SetRelativeRotation(FRotator(10.0, 50.0, 0.0));
		RightMesh->SetRelativeRotation(FRotator(10.0, -10.0, 0.0));
	}
	else {
		LeftMesh->SetRelativeRotation(FRotator(30.0, 50.0, 0.0));
		RightMesh->SetRelativeRotation(FRotator(30.0, -10.0, 0.0));
	}*/
	shaketime = 0;
	lrecoil = 0;
	rrecoil = 0;
	shaking = true;
	if(!shakeupcamera)
		shakeupcamera = true;
}

void AFPSCharacter::ShakeCameraend()
{
	shakingnum = 0;
	shaking = false;
	cameratime = 0;
	LeftMesh->SetRelativeRotation(FRotator(0.0, 50.0, 0.0));
	RightMesh->SetRelativeRotation(FRotator(0.0, -10.0, 0.0));
	FPSCameraComponent->SetRelativeRotation(FRotator(0.0, 0.0, 0.0));
	shaketime = 0;
}

void AFPSCharacter::StartWalk()
{
	walking = true;
}

void AFPSCharacter::StopWalk()
{
	walking = false;
}

void AFPSCharacter::StartSitdown()
{
	RootComponent->SetWorldScale3D(FVector(1.0f,1.0f,0.5f));
}

void AFPSCharacter::StopSitdown()
{
	RootComponent->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}