// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap_Shake_comp.h"
#include "TrapBase.h"
#include "WG/WGCharacter.h"


UTrap_Shake_comp::UTrap_Shake_comp()
{
}

void UTrap_Shake_comp::BeginPlay()
{
	Super::BeginPlay();
}

void UTrap_Shake_comp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AWGCharacter::StaticClass()) ){
	ShakePrepare();
	}
}

void UTrap_Shake_comp::ShakePrepare()
{
	OwnerActor->ChangeMaterialColor(FLinearColor::Yellow);

	bIsShaking = true;
	
	InitialRotation = OwnerActor->GetActorRotation();
	
	GetWorld()->GetTimerManager().SetTimer(ShakeHandler,this, &UTrap_Shake_comp::Shake, 0.05, true);
}

void UTrap_Shake_comp::Shake()
{
	FRotator ShakeDelta(
		0,
		0,
		FMath::RandRange(-ShakeIntensity,ShakeIntensity)
		);

	OwnerActor->SetActorRotation(InitialRotation + ShakeDelta);
		
	ShakeDuration -= 0.05f;

	if (ShakeDuration <= RedFlagDuration)
	{
		OwnerActor->ChangeMaterialColor(FLinearColor::Red);

	}

	if (ShakeDuration <= 0)
	{
		OwnerActor->SetActorRotation(InitialRotation);
		
		AActor* Actor = Cast<AActor>(OwnerActor);
		if (Actor)
		{
			UPrimitiveComponent* MyRootComponent = Actor->FindComponentByClass<UPrimitiveComponent>();
			if (MyRootComponent)
			{
				MyRootComponent->SetSimulatePhysics(true);
				MyRootComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
				GetWorld()->GetTimerManager().SetTimer(DestroyHandler, this, &UTrap_Shake_comp::SelfDestroy,1,false,3);
			}
		}
	}
}



void UTrap_Shake_comp::ResetTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ShakeHandler);
	GetWorld()->GetTimerManager().ClearTimer(DestroyHandler);
}

void UTrap_Shake_comp::SelfDestroy()
{
	OwnerActor->Destroy();
}

