// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap_Wind_comp.h"

#include "TrapBase.h"
#include "Components/BoxComponent.h"

UTrap_Wind_comp::UTrap_Wind_comp()
{
	
}


void UTrap_Wind_comp::BeginPlay()
{
	Super::BeginPlay();

	InteractCollision->SetBoxExtent(FVector(50.f,50.f,1500.f));
	InteractCollision->SetRelativeLocation(FVector(50.f, 50.f,1600.f));
}



void UTrap_Wind_comp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTrap_Wind_comp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OverlappedComp == InteractCollision)
	{
		Wind(OtherActor);
	}
}

void UTrap_Wind_comp::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	GetWorld()->GetTimerManager().ClearTimer(WindTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(WindChangeHandle);
	OwnerActor->ChangeMaterialColor(FLinearColor::Gray);
}

void UTrap_Wind_comp::Wind(AActor* OtherActor)
{
	OwnerActor->ChangeMaterialColor(FLinearColor::Blue);
	
	auto WindApplyLambda = [this, OtherActor]()
	{
		WindApply(OtherActor);
	};
	
	GetWorld()->GetTimerManager().SetTimer(WindChangeHandle,WindApplyLambda,WindChangeRate,true, 0.f);
}

void UTrap_Wind_comp::WindApply(AActor* OtherActor)
{
	
	float BetterRandomDirection = 0.f;
	if (bWindRight)
	{
		BetterRandomDirection =  FMath::RandRange(30.f,MaxYAxisPower);
	}
	if (!bWindRight)
	{
		BetterRandomDirection =  FMath::RandRange(MinYAxisPower,-30.f);
	}
	
	bWindRight = !bWindRight;
	
	FVector WindDirection = FVector(0.f, BetterRandomDirection, 0.f);
	
	auto WindChangeLambda = [this, OtherActor, WindDirection]()
	{
		WindChange(OtherActor,WindDirection);
	};
	
	GetWorld()->GetTimerManager().ClearTimer(WindTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(WindTimerHandle,WindChangeLambda,WindPressure*GetWorld()->GetDeltaSeconds(),true);
}

void UTrap_Wind_comp::WindChange(AActor* OtherActor, FVector WindDirection)
{
	FVector TargetLocation = OtherActor->GetActorLocation() + WindDirection;

	// Not sure i need VInterpTo. May be just velocity*deltatime?
	// But as player, filling wind better. 
	FVector newLocation = FMath::VInterpTo(OtherActor->GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), 1);
	OtherActor->SetActorLocation(newLocation);
}

void UTrap_Wind_comp::ResetTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(WindTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(WindChangeHandle);
}