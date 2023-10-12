#include "Trap_MovingPlatform_comp.h"
#include "TrapBase.h"
#include "Components/BoxComponent.h"

UTrap_MovingPlatform_comp::UTrap_MovingPlatform_comp()
{
}

void UTrap_MovingPlatform_comp::BeginPlay()
{
	Super::BeginPlay();
}

void UTrap_MovingPlatform_comp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTrap_MovingPlatform_comp::MovingPlatform()
{
	bEnd = false;
	StartPoint = OwnerActor->GetActorLocation();
	EndPoint = InteractCollision->GetComponentLocation();
	
	GetWorld()->GetTimerManager().SetTimer(TransitionHandle,this, &UTrap_MovingPlatform_comp::MoveObject, 1*GetWorld()->GetDeltaSeconds() ,true,0);
	
}

void UTrap_MovingPlatform_comp::MoveObject()
{
	FVector CurrentLocation;
	FVector TargetLocation;
	
	if (!bEnd)
	{
		CurrentLocation = OwnerActor->GetActorLocation();
		TargetLocation = CurrentLocation + (FVector(EndPoint.X - StartPoint.X, EndPoint.Y - StartPoint.Y,EndPoint.Z - StartPoint.Z)/PlatformVelocityInSec) * GetWorld()->GetDeltaSeconds();

		if (CurrentLocation.Equals(EndPoint, 3.f))
		{
			bEnd = !bEnd;
		}
	}
	if (bEnd)
	{
		CurrentLocation = OwnerActor->GetActorLocation();
		TargetLocation = CurrentLocation + (FVector(StartPoint.X - EndPoint.X, StartPoint.Y - EndPoint.Y,StartPoint.Z - EndPoint.Z)/PlatformVelocityInSec) * GetWorld()->GetDeltaSeconds();
		if (CurrentLocation.Equals(StartPoint, 3.f))
		{
			bEnd = !bEnd;
		}
	}
	OwnerActor->SetActorLocation(TargetLocation);
}


void UTrap_MovingPlatform_comp::ResetTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TransitionHandle);
}


