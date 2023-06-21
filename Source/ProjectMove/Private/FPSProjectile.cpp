// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��ü�� �ܼ� �ݸ��� ǥ������ ����մϴ�.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	//��ü �ݸ��� �ݰ� ����
	CollisionComponent->InitSphereRadius(5.0f);
	//��Ʈ ������Ʈ�� �ݸ��� ������Ʈ�� ����.
	RootComponent = CollisionComponent;

	//ProjectileMovementComponent �� ����Ͽ� �߻�ü�� ��� ����
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 4000.0f;
	ProjectileMovementComponent->MaxSpeed = 4000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	//3�ʸ� �������
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSProjectile::OnComponentBeginOverlap);
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSProjectile::FireInDirection(const FVector&ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory,GetActorLocation(), FRotator(), FVector(1, 1, 1));
	UE_LOG(LogTemp, Log, TEXT("block"));
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
}

void AFPSProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("overlap"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodFactory, GetActorLocation(), FRotator(), FVector(1, 1, 1));
	Destroy();
}

bool AFPSProjectile::IsCharacter(AActor* checkActor)
{
	/*Character* Character = Cast<ACharacter>(checkActor);
	if (Character != nullptr)
	{
		return true;
	}*/
	return false;
}
