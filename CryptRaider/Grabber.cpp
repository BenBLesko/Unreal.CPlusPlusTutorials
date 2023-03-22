


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


UGrabber::UGrabber()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UGrabber::BeginPlay()
{

	Super::BeginPlay();


}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle -> GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle -> SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbaleInReach(HitResult);
	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent -> WakeAllRigidBodies();
		HitResult.GetActor() -> Tags.Add("Grabbed");
		PhysicsHandle -> GrabComponentAtLocationWithRotation
		(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle -> GetGrabbedComponent())
	{
		PhysicsHandle -> GetGrabbedComponent() -> WakeAllRigidBodies();
		AActor* GrabbedActor = PhysicsHandle -> GetGrabbedComponent() -> GetOwner();
		GrabbedActor -> Tags.Remove("Grabbed");
		PhysicsHandle -> ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent!"));
	}
	return Result;
}

bool UGrabber::GetGrabbaleInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld() -> SweepSingleByChannel
	(
		OutHitResult, 
		Start, End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
	);
}
