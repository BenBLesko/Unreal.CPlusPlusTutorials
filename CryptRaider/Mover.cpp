


#include "Mover.h"
#include "Math/UnrealMathUtility.h"


UMover::UMover()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UMover::BeginPlay()
{

	Super::BeginPlay();


	OriginalLocation = GetOwner()->GetActorLocation();
	MovedOnYLocation = GetOwner()->GetActorLocation() + MoveOffsetY;
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	if (ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		FVector TargetLocationY = OriginalLocation + MoveOffsetY;
		float SpeedY = FVector::Distance(OriginalLocation, TargetLocationY) / MoveTime;
		FVector NewLocationY = FMath::VInterpConstantTo(CurrentLocation, TargetLocationY, DeltaTime, SpeedY);

		GetOwner()->SetActorLocation(NewLocationY);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
		IsMovedOnY = true;
		}, 4, false);
	}

	if (IsMovedOnY)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		FVector TargetLocationX = MovedOnYLocation + MoveOffsetX;
		float SpeedX = FVector::Distance(MovedOnYLocation, TargetLocationX) / MoveTime;
		FVector NewLocationX = FMath::VInterpConstantTo(CurrentLocation, TargetLocationX, DeltaTime, SpeedX);

		GetOwner()->SetActorLocation(NewLocationX);
	}
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}
