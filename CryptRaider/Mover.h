

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UMover();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool ShouldMove);

private:
	
	UPROPERTY(EditAnywhere)
	FVector MoveOffsetY;
	UPROPERTY(EditAnywhere)
	FVector MoveOffsetX;

	UPROPERTY(EditAnywhere)
	float MoveTime = 4;

	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;
	UPROPERTY(EditAnywhere)
	bool IsMovedOnY = false;

	FVector OriginalLocation;
	FVector MovedOnYLocation;

};
