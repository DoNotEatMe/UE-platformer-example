#include "Trap_Hiding_comp.h"
#include "TrapBase.h"
#include "Kismet/GameplayStatics.h"
#include "WG/trigger.h"

UTrap_Hiding_comp::UTrap_Hiding_comp()
{
}

void UTrap_Hiding_comp::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Triggers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),Atrigger::StaticClass(),Triggers);
	for (AActor* Actor : Triggers)
	{
		Atrigger* Trigger = Cast<Atrigger>(Actor);
		if (Trigger)
		{
			Trigger->TrapsStart.AddDynamic(this,&UTrap_Hiding_comp::HidingTrap);
		}
		
	}
}

void UTrap_Hiding_comp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTrap_Hiding_comp::HidingTrap()
{
	GetWorld()->GetTimerManager().SetTimer(HidingTrapHandler,this,&UTrap_Hiding_comp::HideUnhide,HidingRate,true, StartDelay);
}

void UTrap_Hiding_comp::HideUnhide()
{
	UPrimitiveComponent* PlatformRootComp = OwnerActor->FindComponentByClass<UPrimitiveComponent>();

	if (!OwnerActor->IsHidden())
	{
		OwnerActor->SetActorHiddenInGame(true);
		
		if (PlatformRootComp)
		{
			PlatformRootComp->SetCollisionResponseToAllChannels(ECR_Ignore);
		}
	}
	else
	{
		OwnerActor->SetActorHiddenInGame(false);
		if (PlatformRootComp)
		{
			PlatformRootComp->SetCollisionResponseToAllChannels(ECR_Block);
		}
	}
}
