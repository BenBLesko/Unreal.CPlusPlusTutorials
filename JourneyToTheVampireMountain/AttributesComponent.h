

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DirectionalLight.h" // to be able to get a reference for the Directional Light
#include "AttributesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWVAMPIRESIMULATOR_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAttributesComponent();

protected:
	
	virtual void BeginPlay() override;
	
	// Health and Blood Points values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float maxHealth = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float currentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float maxBloodPoints = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float currentBloodPoints;
	
	// Blood Vial consumables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float maxBloodVials = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float currentBloodVials = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float addBloodPointsByBloodVials = 0.30f;
	
	// damage types
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float emptyBloodPointsHealthDMG = 0.01f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float sunHealthDMG = 0.20f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float flittingBloodPointsDMG = 0.33f;
	// healing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float healingHealth = 0.10f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float healingBloodPointsDMG = 0.10f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metrics")
	float skillBloodPointsDMG = 0.33f;

	// 'Sunlight Detection' Function
	UFUNCTION(BlueprintCallable)
	void SunlightDetection(bool& ReturnValue);
	// values for the 'Sunlight Detection' Function
	FVector playerLocation;
	UPROPERTY(EditAnywhere, Category="Sky")
	TSoftObjectPtr<ADirectionalLight> directionalLight;
	FVector lightSourceFVector;
	FVector lightSourceNewFVector;
	
	// 'Blood Points Loss' Function
	UFUNCTION(BlueprintCallable)
	void BloodPointsLoss();
	
	// 'Sunlight Damage' Function
	UFUNCTION(BlueprintCallable)
	void SunlightDMG();
	
	// 'Consuming Blood Vial' Function
	UFUNCTION(BlueprintCallable)
	void ConsumingBloodVial();
	
	// 'Healing Factor' Function
	UFUNCTION(BlueprintCallable)
	void HealingFactor();

private:
	
	

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 'Skill Damage' Function
	UFUNCTION(BlueprintCallable)
	void SkillDMG();
	
	// 'Game Over' bool
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Win Condition")
	bool isGameOver;

};
