
#include "Trap_Explosive_comp.h"

#include "TrapBase.h"
#include "Components/BoxComponent.h"
#include "WGCharacter.h"



UTrap_Explosive_comp::UTrap_Explosive_comp()
{

	PrimaryComponentTick.bCanEverTick = true;


	// init
	bIsTrapCooldown = false;

	OwnerActor = nullptr;
	DynamicMaterial = nullptr;
	InteractCollision = nullptr;
	
}

void UTrap_Explosive_comp::BeginPlay()
{
	Super::BeginPlay();

	// Prepare Owner
	AActor* Actor = GetOwner();
	if (Actor)
	{
		OwnerActor = Cast<ATrapBase>(Actor);
		if (!OwnerActor)
		{
			UE_LOG(LogTemp,Error,TEXT("Trap_Explosive_comp %s cannot get OwnerActor"), *this->GetOwner()->GetName());
		}
	}
	

	// Prepare material
	UStaticMeshComponent* Platform = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (Platform)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(Platform->GetMaterial(0), this);
	}


	// Prepare Collision
	InteractCollision = Cast<UBoxComponent>(GetOwner()->GetDefaultSubobjectByName("Interact Collision"));
	if (InteractCollision){
	InteractCollision->OnComponentBeginOverlap.AddDynamic(this, &UTrap_Explosive_comp::OnOverlapBegin);
	} else
	{
		UE_LOG(LogTemp,Error,TEXT("InteractCollision lost at %s --Trap_Explosive_comp"), *this->GetOwner()->GetName());
	}
	UE_LOG(LogTemp,Warning,TEXT("Explosive Trap here"));
}


// Called every frame
void UTrap_Explosive_comp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTrap_Explosive_comp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComp == InteractCollision)
	{
		ExplodePrepare(OtherActor);
		SetTrapCooldown(OtherActor);
		UE_LOG(LogTemp,Warning,TEXT("Overlapped %s"), *GetOwner()->GetName());
	}
	
}

void UTrap_Explosive_comp::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}




void UTrap_Explosive_comp::ExplodePrepare(AActor* OtherActor)
{
	if(InteractCollision->IsOverlappingActor(OtherActor)){
		
		OwnerActor->ChangeMaterialColor(FLinearColor::Yellow);
		
		auto Lambda = [this, OtherActor]()
		{
			Explode(OtherActor);
		};
		
		GetWorld()->GetTimerManager().SetTimer(ExplodeTimerHandle, Lambda, TimeForExplosion, false);
	
	}
}



void UTrap_Explosive_comp::Explode(AActor* OtherActor)
{
	OwnerActor->ChangeMaterialColor(FLinearColor::Red);

	// Cause damage to all players that stand at the platform
	// In case that is solo game, there is no need to cause damage to all players that stand on platform
	// We could make same thing just one with if CollisionComp->IsOverlappingActor(OtherActor)
	// But in case of test work we will get TArray of actors and cause damage to each who is a Player
	TArray<AActor*> OverlappingActors;
	InteractCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		AWGCharacter* Character = Cast<AWGCharacter>(Actor);
		if (Character)
		{
			FDamageEvent DamageEvent;
			OnApplyDamage.Broadcast(TrapDamage, this->GetOwner(),DamageEvent);
		}
	}
	
	
	GetWorld()->GetTimerManager().SetTimer(RedColorTimerHandle, this, &UTrap_Explosive_comp::ResetMaterial, MaterialResetTime, false);

	if(InteractCollision->IsOverlappingActor(OtherActor) && bIsTrapCooldown == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Calling ExplodePrepare in case of trap overlapping actor"));
		auto Lambda = [this, OtherActor]()
		{
			ExplodePrepare(OtherActor);
		};
			
		GetWorld()->GetTimerManager().SetTimer(ExplodeCooldownHandle, Lambda, 0, true);
	}
	
}

void UTrap_Explosive_comp::ResetMaterial()
{
	OwnerActor->ChangeMaterialColor(FLinearColor::Gray);
}


void UTrap_Explosive_comp::SetTrapCooldown(AActor* OtherActor)
{
	bIsTrapCooldown = true;
	
	auto Lambda = [this, OtherActor]()
	{
		ResetTrapCooldown(OtherActor);
	};
	
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, Lambda,CooldownDuration, false);
}

void UTrap_Explosive_comp::ResetTrapCooldown(AActor* OtherActor)
{
	bIsTrapCooldown = false;

	if (OtherActor && OtherActor->IsA<AWGCharacter>() && InteractCollision->IsOverlappingActor(OtherActor))
	{
		ExplodePrepare(OtherActor);
		SetTrapCooldown(OtherActor); 
	}
}

void UTrap_Explosive_comp::ResetTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ExplodeTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(RedColorTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ExplodeCooldownHandle);
	GetWorld()->GetTimerManager().ClearTimer(CooldownHandle);
}
