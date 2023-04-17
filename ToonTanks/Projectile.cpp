


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent -> MaxSpeed = 0.f;
	ProjectileMovementComponent -> InitialSpeed = 0.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	

	ProjectileMesh -> OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor *OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr) return;

	auto MyOwnerInstigator = MyOwner -> GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
	}
	if (HitCameraShakeClass)
	{
		GetWorld() -> GetFirstPlayerController() -> ClientStartCameraShake(HitCameraShakeClass);
	}
	Destroy();
}

