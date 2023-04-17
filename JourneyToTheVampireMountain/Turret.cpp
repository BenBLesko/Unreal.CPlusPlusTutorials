


#include "Turret.h"
#include "Components/StaticMeshComponent.h" // for the components
#include "Components/SpotLightComponent.h" // for the componets
#include "AttributesComponent.h" // to get access to AttributesComponent
#include "Kismet/GameplayStatics.h"


ATurret::ATurret()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	// components
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh -> SetupAttachment(BaseMesh);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light"));
	SpotLight -> SetupAttachment(TurretMesh);

	SpotLightCone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot Light Cone"));
	SpotLightCone -> SetupAttachment(TurretMesh);

}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	

	isSwitched = false;
	SpotLight -> ToggleVisibility();

	// for the 'OnOverlapBegin' Function
	SpotLightCone -> OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBegin);
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



}

// 'Set Switch' Function
void ATurret::SetSwitch()
{
	isSwitched = true;
	SpotLight -> ToggleVisibility();
}

// 'Rotation' Function
void ATurret::RotateTurret()
{
	if (isSwitched)
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		TurretMesh -> AddLocalRotation(FRotator(0, (RotationSpeed * DeltaTime), 0));
	}
}

// 'OnOverlapBegin' Function
void ATurret::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (isSwitched)
	{
		if (OtherActor)
		{
			// set the 'GameOver?' bool true in the AttributesComponent
			Player -> FindComponentByClass<UAttributesComponent>() -> isGameOver = true;
		}
	}
}
