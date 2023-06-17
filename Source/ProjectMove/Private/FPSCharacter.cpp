// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "FPSProjectile.h"
#include "GameFramework/Character.h"
#include "HillPack.h"
#include "AssaultRifle.h"
#include "AmmoPack.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	
	// ����Ī �޽� ������Ʈ�Դϴ�.
	RightMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightMesh"));
	//RightMesh->SkeletalMesh->AddSocket(SocketMesh);
	// ���� �÷��̾ �� �޽ø� �� �� �ֽ��ϴ�.
	RightMesh->SetOnlyOwnerSee(true);
	// FPS �޽ø� FPS ī�޶� ���Դϴ�.
	RightMesh->SetupAttachment(FPSCameraComponent);
	// �Ϻ� ȯ�� �������� �� �޽ð� �ϳ��� �� ���̴� ������ �����մϴ�.
	RightMesh->bCastDynamicShadow = false;
	RightMesh->CastShadow = false;
	GetMesh()->SetOwnerNoSee(false);
	RightMesh->SetRelativeLocation(FVector(0.0f, 10.0f, -210.0f));
	RightMesh->SetRelativeRotation(FRotator(0.0, -100.0, 0.0));
	RightMesh->SetWorldScale3D(FVector(1.75, 1.45, 1.25));
	
	//ó�� ���� 1
	WeaponNum = 1;
	Ammo = 30;
	Leftammo = 0;
	Weapon1bullet = 0;
	Weapon2bullet = 10;
	Weapon3bullet = 3;
	HP = 100;
	firing = false;
	currentTime = 0;
	firetime = 0.2f;
	shakeupcamera = false;
	shakedowncamera = false;
	//ī�޶� Ÿ�� üũ
	checkcameratime = false;
	reloading = false;
	reloadtime = 0;
	//�ҷ��ͼ� �ٿ�����
	ConstructorHelpers::FObjectFinder<UAnimationAsset>TempAinm(TEXT("/Script/Engine.AnimSequence'/Game/Animations/Reloading_Anim.Reloading_Anim'"));
	if (TempAinm.Succeeded())
	{
		ReloadAinm = TempAinm.Object;
	}
	linedelaytime = 0;
	GetCharacterMovement()->JumpZVelocity = GetCharacterMovement()->JumpZVelocity*0.6;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// 5 �ʰ� ����� �޽����� ǥ���մϴ�. (ù �μ���) -1 "Key" ���� �� �޽����� ������Ʈ �Ǵ� ���ΰ�ĥ �ʿ䰡 ������ ��Ÿ���ϴ�.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
		
		AttachWeapon(_weapon);
		equip_weapon->Destroy();
		equip_weapon = nullptr;
	}
	HillPackNum = 0;
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
	if (checkcameratime) {
		cameratime += DeltaTime;
		shaketime += DeltaTime;
	}
	if (shaking) {
		if (shakingnum % 2 == 0)
		{
			RightMesh->SetRelativeLocation(FVector(0.0f-(10.0f * ((shaketime - lrecoil) / 0.05f)), 10.0f, -210.0f));
			AddControllerPitchInput(-0.6f * ((shaketime - lrecoil) / 0.05f));
			lrecoil = shaketime;
		}
		else
		{
			RightMesh->SetRelativeLocation(FVector(-10.0f + (10.0f * ((shaketime - rrecoil) / 0.05f)), 10.0f, -210.0f));
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
				RightMesh->SetRelativeRotation(FRotator(0.0, -100.0, -2.0 * (cameratime / 0.1f)));
			}
			else {
				RightMesh->SetRelativeRotation(FRotator(0.0, -100.0, -2.0 * (cameratime / 0.1f)));
			}
		}
	}
	if (cameratime >= 0.3f) {
			shakedowncamera = false;
			shakeupcamera = false;
			cameratime = 0;
			ShakeCameraend();
			UE_LOG(LogTemp, Log, TEXT("checking"));
	}
	if (reloading) {
		reloadtime += DeltaTime;
		if (reloadtime >= 3.0f) {
			equip_weapon->Reloading(this);
			reloading = false;
			reloadtime = 0;
		}
	}

	//����Ʈ���̽�
	linedelaytime += DeltaTime;
	if (linedelaytime >= 0.1f)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		FVector start = CameraLocation;
		start.Z -= 18.5f;
		FVector end = (CameraRotation.Vector() * 400.0f) + start;
		FHitResult hitResult;
		FCollisionQueryParams collisionParams;
		collisionParams.AddIgnoredActor(this);
		//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 1.0f);
		if (GetWorld()->LineTraceSingleByChannel(
			hitResult,
			start,
			end,
			ECC_Visibility,
			collisionParams))
		{
			if (hitResult.GetActor())
			{
				auto* hitActor = hitResult.GetActor();
				//�����¾Ҵ��� Ȯ�ο�
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Hit Actor Name:%s"), *hitActor->GetName()));
			}
		}
		linedelaytime = 0;
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
	PlayerInputComponent->BindAction("Logiccheck", IE_Released, this, &AFPSCharacter::Logiccheck);
	//��ȣ�ۿ� ���ε�
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &AFPSCharacter::Interaction);
	//���� �ӽ�
	PlayerInputComponent->BindAction("Healing", IE_Released, this, &AFPSCharacter::Heal);
}

void AFPSCharacter::MoveForward(float Value)
{
	//������� �������� �˾Ƴ��� �÷��̾ �׹������� �̵��ϰ��� �Ѵٰ� ����մϴ�.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	if (walking)
	{
		AddMovementInput(Direction*0.2, Value);
	}
	else
	AddMovementInput(Direction*0.4, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	if (walking)
	{
		AddMovementInput(Direction * 0.2, Value);
	}
	else
	AddMovementInput(Direction * 0.4, Value);
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
		if (!sitdowncheck)
			MuzzleLocation.Z += 50.0f;
		else
			MuzzleLocation.Z -= 10.0f;
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
		/*WeaponMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
		WeaponMesh->SetRelativeLocation(FVector(90.0f, 40.0f, 100.0f));*/
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
		//WeaponMesh->SetRelativeScale3D(FVector(0.5f, 1.0f, 1.0f));
		//WeaponMesh->SetRelativeLocation(FVector(70.0f, 40.0f, 100.0f));
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
		/*WeaponMesh->SetRelativeScale3D(FVector(0.25f, 1.0f, 1.0f));
		WeaponMesh->SetRelativeLocation(FVector(60.0f, 40.0f, 100.0f));*/
		Ammo = 3;
		Leftammo = Weapon3bullet;
	}

}
void AFPSCharacter::Reload()
{
	if (!reloading)
	{
		if (equip_weapon!=nullptr)
		{
			reloading = true;
			reloadtime = 0;
			if (ReloadAinm != nullptr)
			{
				RightMesh->PlayAnimation(ReloadAinm, false);
			}
		}
	}
	
}

void AFPSCharacter::FireCheck()
{

	/*if (WeaponNum == 1)
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
	}*/
	if (equip_weapon!=nullptr&&!reloading)
	{
			equip_weapon->StartFire(this);
	}
}

void AFPSCharacter::FireStop()
{
	/*if (WeaponNum == 1) {
		firing = false;
		UE_LOG(LogTemp, Log, TEXT("firing=%d"), firing);
		currentTime = 0;
	}*/
	if (equip_weapon!=nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("FireStop"));
		equip_weapon->StopFire();
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

void AFPSCharacter::Heal()
{
	int32 healing = 50;
	if (HillPackNum > 0) {
		if (HP==100)
		{
			;
		}
		else if (HP + healing >= 100) {
			HP = 100;
			HillPackNum--;
		}
		else {
			HP += healing;
			HillPackNum--;
		}
	}
}


void AFPSCharacter::ShakeCamerastart()
{
	shakingnum = 0;
	cameratime = 0;
	shaketime = 0;
	lrecoil = 0;
	rrecoil = 0;
	shaking = true;
	checkcameratime = true;
	if(!shakeupcamera)
		shakeupcamera = true;
}

void AFPSCharacter::ShakeCameraend()
{
	shakingnum = 0;
	shaking = false;
	checkcameratime = false;
	cameratime = 0;
	RightMesh->SetRelativeRotation(FRotator(0.0, -100.0, 0.0));
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
	sitdowncheck = true;
	RootComponent->SetWorldScale3D(FVector(0.4f, 0.4f,0.2f));
}

void AFPSCharacter::StopSitdown()
{
	RootComponent->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
	sitdowncheck = false;
}

bool AFPSCharacter::GetReload()
{
	return reloading;
}

//�ѱ� ���̱�
void AFPSCharacter::AttachWeapon(TSubclassOf<class AWeapon> weapon) 
{
	if (weapon)
	{
		equip_weapon = GetWorld()->SpawnActor<AWeapon>(weapon);
		const USkeletalMeshSocket* weaponSocket = RightMesh->GetSocketByName("WeaponSocket");
		if (equip_weapon != nullptr && weaponSocket)
		{
			weaponSocket->AttachActor(equip_weapon, RightMesh);
		}
	}
}

//��ȣ�ۿ�
void AFPSCharacter::Interaction()
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);
	FVector start = CameraLocation;
	start.Z -= 18.5f;
	FVector end = (CameraRotation.Vector() * 400.0f) + start;
	FHitResult hitResult;
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);
	//DrawDebugLine(GetWorld(), start, end, FColor::Blue, false, 1.0f);
	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		start,
		end,
		ECC_Visibility,
		collisionParams))
	{
		if (hitResult.GetActor())
		{
			auto* hitActor = hitResult.GetActor();
			//�����¾Ҵ��� Ȯ�ο�
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Hit Actor Name:%s"), *hitActor->GetName()));
			AWeapon* HitWeapon = Cast<AWeapon>(hitActor);
			if (HitWeapon!=nullptr)
			{
				AHillPack* isHillPack = Cast<AHillPack>(HitWeapon);
				if (isHillPack != nullptr)
				{
					hitActor->Destroy();
					HillPackNum++;
				}
				else
				{
					AAmmoPack* isAmmoPack = Cast<AAmmoPack>(HitWeapon);
					if (isAmmoPack != nullptr) {
						Weapon1bullet = 180;
					}
					else
					{
						AAssaultRifle* isAssaultRifle = Cast<AAssaultRifle>(HitWeapon);
						if (isAssaultRifle != nullptr)
						{
							if (equip_weapon != nullptr)
							{
								if (Weapon1bullet + Leftammo >= 180)
								{
									Weapon1bullet = 180;
								}
								else
								{
									Weapon1bullet += Leftammo;

								}
								Leftammo = 0;
								equip_weapon->Destroy();
								equip_weapon = nullptr;
							}
							equip_weapon = isAssaultRifle;
							Leftammo = 30;
							const USkeletalMeshSocket* weaponSocket = RightMesh->GetSocketByName("WeaponSocket");
							if (equip_weapon != nullptr && weaponSocket)
							{
								weaponSocket->AttachActor(equip_weapon, RightMesh);
							}
						}
					}
				}
			}
		}
	}
}






//////////////����

void AFPSCharacter::Logiccheck()
{
	equip_weapon->Destroy();
	equip_weapon = nullptr;
}