


#include "AttributesComponent.h"
#include "Engine/World.h" // to be able to use 'Line Trace by Single Channel'
#include "Kismet/KismetSystemLibrary.h" // to be able to use 'Line Trace by Single Channel'
#include "Math/Vector.h" // for Math
#include "Math/UnrealMathUtility.h" // for Math
#include "Misc/OutputDeviceNull.h" // for Null Output Device
#include "DrawDebugHelpers.h" // to be able to draw debug lines


UAttributesComponent::UAttributesComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}

void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	
	isGameOver = false;
}

void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	
}

// 'Sunlight Detection' Function
void UAttributesComponent::SunlightDetection(bool& ReturnValue)
{
	playerLocation = GetOwner()->GetActorLocation(); // get the Character's Location
	if (directionalLight)
	{
		lightSourceFVector = directionalLight -> GetActorForwardVector(); // get the Directional Light's initial FVector
		lightSourceNewFVector = lightSourceFVector.operator*(-1000); // multiply the Directional Light's initial FVector by -1000

		// Line Trace by Single Channel
		FHitResult HitResult;
		FVector StartPoint = playerLocation;
		FVector EndPoint = playerLocation + lightSourceNewFVector;
		FCollisionQueryParams Parameters;
		bool hitCheck;
		hitCheck = GetWorld() -> LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, Parameters);
		//// DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Green, true, 1.0f);

		if (hitCheck)
		{
			ReturnValue = true;
			//// UE_LOG(LogTemp, Display, TEXT("NOT exposed to Sunlight!"));
		}

		if (!hitCheck)
		{
			ReturnValue = false;
			//// UE_LOG(LogTemp, Display, TEXT("Exposed to Sunlight!"));
		}
	}
}

// 'Blood Points Damage' Function
void UAttributesComponent::BloodPointsLoss()
{
	if (currentBloodPoints <= 0.01f) // if the current Blood Points value is less or equal to 0.01 
	{
		currentHealth = currentHealth - emptyBloodPointsHealthDMG; // then take damage from the current Health value

		// bugfix and Game Over
		if (currentHealth <= 0.01f)
		{
			currentHealth = 0.f;
			isGameOver = true;
		}
	}
}

// 'Sunlight Damage' Function
void UAttributesComponent::SunlightDMG()
{
	currentHealth = currentHealth - sunHealthDMG; // deals damage to the current Health value
		
	// bugfix and Game Over
	if (currentHealth <= 0.01f)
	{
		currentHealth = 0.f;
		isGameOver = true;
	}
}

// 'Consuming Blood Vial' Function
void UAttributesComponent::ConsumingBloodVial()
{
	--currentBloodVials; // use up one Blood Vials
	currentBloodPoints = currentBloodPoints + addBloodPointsByBloodVials; // add to the current Blood Points value

		// bugfix
		if (currentBloodPoints >= maxBloodPoints)
		{
			currentBloodPoints = maxBloodPoints;
		}
		// bugfix
		if (currentBloodVials <= 0.01f)
		{
			currentBloodVials = 0.f;
		}
}

// 'Healing Factor' Function
void UAttributesComponent::HealingFactor()
{
	if (currentBloodPoints > 0.01f) // if the current Blood Points value is greater or equal to 0.01 
	{
		currentHealth = currentHealth + healingHealth; // then add to the current Health value
		if (currentHealth <= maxHealth)
		{
			currentBloodPoints = currentBloodPoints - healingBloodPointsDMG; // and take increased Blood Points loss
		}
			// bugfix
			if (currentHealth >= 1.f)
			{
				currentHealth = maxHealth;
			}
	}
}

// 'Skill Damage' Function
void UAttributesComponent::SkillDMG()
{
		currentBloodPoints = currentBloodPoints - skillBloodPointsDMG;

			// bugfix
			if (currentBloodPoints <= 0.01f)
			{
				currentBloodPoints = 0.f;
			}
}