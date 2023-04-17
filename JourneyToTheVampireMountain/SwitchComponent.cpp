


#include "SwitchComponent.h"
#include "Misc/OutputDeviceNull.h" // for Null Output Device
#include "AttributesComponent.h" // to get access to AttributesComponent


USwitchComponent::USwitchComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}

void USwitchComponent::BeginPlay()
{
	Super::BeginPlay();
	
	

}

void USwitchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	
}

// 'Set Time of Day Forward' Function
void USwitchComponent::SetTimeOfDayForward()
{
	float DeltaTime = GetWorld() -> GetDeltaSeconds(); // to get the Delta Seconds

	if (directionalLight)
	{
		directionalLight -> AddActorLocalRotation(FRotator(0, (DeltaTime * turnRate), 0));
			// to call a Blueprint function to update the Sun's direction in the BP_Sky_Sphere
			if (Sun)
			{
				FOutputDeviceNull ar;
				Sun -> CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
			}
	
		Player -> FindComponentByClass<UAttributesComponent>() -> SkillDMG(); // to call the 'Skill DMG' Function from the Player
	}
}

// 'Set Time of Day Backward' Function
void USwitchComponent::SetTimeOfDayBackward()
{
	float DeltaTime = GetWorld() -> GetDeltaSeconds(); // to get the Delta Seconds

	if (directionalLight)
	{	
		directionalLight -> AddActorLocalRotation(FRotator(0, (DeltaTime * -turnRate), 0));
			// to call a Blueprint function to update the Sun's direction in the BP_Sky_Sphere
			if (Sun)
			{
				FOutputDeviceNull ar;
				Sun -> CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
			}

		Player -> FindComponentByClass<UAttributesComponent>() -> SkillDMG(); // to call the 'Skill DMG' Function from the Player
	}
}

// 'Set Sun Rotation' Function
void USwitchComponent::SetSunRotation()
{
	float DeltaTime = GetWorld() -> GetDeltaSeconds(); // to get the Delta Seconds

	if (directionalLight)
	{
		directionalLight -> SetActorRotation(FRotator(-10, -30, 90));
			// to call a Blueprint function to update the Sun's direction in the BP_Sky_Sphere
			if (Sun)
			{
				FOutputDeviceNull ar;
				Sun -> CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
			}
	
		Player -> FindComponentByClass<UAttributesComponent>() -> SkillDMG(); // to call the 'Skill DMG' Function from the Player
	}
}

