

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DirectionalLight.h" // to be able to get a reference for the Directional Light
#include "SwitchComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWVAMPIRESIMULATOR_API USwitchComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USwitchComponent();

protected:
	
	virtual void BeginPlay() override;

	// 'Set Sun Rotation Forward' Function
	UFUNCTION(BlueprintCallable)
	void SetTimeOfDayForward();
	// 'Set Sun Rotation Backward' Function
	UFUNCTION(BlueprintCallable)
	void SetTimeOfDayBackward();
	UFUNCTION(BlueprintCallable)
	void SetSunRotation();
	
	// values for the 'Set Sun Rotation' Functions
	UPROPERTY(EditAnywhere, Category="Sky")
	TSoftObjectPtr<ADirectionalLight> directionalLight;
	UPROPERTY(EditAnywhere, Category="Sky")
	TObjectPtr<AActor> Sun;
	UPROPERTY(EditAnywhere, Category="Sky")
	float turnRate;
	UPROPERTY(EditAnywhere, Category="Player")
	TObjectPtr<AActor> Player = GetOwner();

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
