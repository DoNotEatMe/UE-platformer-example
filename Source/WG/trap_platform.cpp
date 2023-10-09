// Fill out your copyright notice in the Description page of Project Settings.


#include "trap_platform.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WGCharacter.h"

// Sets default values
Atrap_platform::Atrap_platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>("Platform");
	RootComponent = Platform;
		
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Collision");
	CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->SetRelativeLocation(FVector(0.0f,0.0f,0.0f));
	CollisionComp->SetBoxExtent(FVector(1.0f,1.0f,1.0f));

	bIsTrapCooldown = false;
	
}



// Called when the game starts or when spawned
void Atrap_platform::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &Atrap_platform::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &Atrap_platform::OnOverlapEnd);

}



// Called every frame
void Atrap_platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void Atrap_platform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
	if(this->ActorHasTag("Explode")){
		if (bIsTrapCooldown == false){
			ExplodePrepare(OtherActor);
			SetTrapCooldown(OtherActor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("bIsTrapPrepare true at OnOverlapBegin"));
		}
		return;
	}
	if(this->ActorHasTag("Wind")){
		Wind(OtherActor);
		return;
	}
	
}

void Atrap_platform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(this->ActorHasTag("Explode")){
		
		return;
	}
	if(this->ActorHasTag("Wind")){
		GetWorldTimerManager().ClearTimer(WindTimerHandle);
		GetWorldTimerManager().ClearTimer(WindChangeHandle);
		ResetMaterial();
		return;
	}
	
}


void Atrap_platform::ExplodePrepare(AActor* OtherActor)
{
	if(CollisionComp->IsOverlappingActor(OtherActor)){
		
		UMaterialInterface* MatChange = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Engine/TemplateResources/MI_Template_BaseOrange.MI_Template_BaseOrange'"));

		if(MatChange){
			Platform->SetMaterial(0, MatChange);
		}
		
		auto Lambda = [this, OtherActor]()
		{
			Explode(OtherActor);
		};
		
		UE_LOG(LogTemp, Warning, TEXT("Explode preparation passed."));
		
		GetWorldTimerManager().SetTimer(ExplodeTimerHandle, Lambda, ExplodeTime, false);
	
	}
}

void Atrap_platform::Explode(AActor* OtherActor)
{
	UMaterialInterface* MatChange = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Engine/VREditor/LaserPointer/LaserPointerMaterial.LaserPointerMaterial'"));
	if (MatChange)
	{
		Platform->SetMaterial(0, MatChange);
	}

	// Cause damage to all players that stand at the platform
	// In case that is solo game, there is no need to cause damage to all players that stand on platform
	// We could make same thing just one with if CollisionComp->IsOverlappingActor(OtherActor)
	// But in case of test work we will get TArray of actors and cause damage to each who is a Player

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && CollisionComp->IsOverlappingActor(Actor))
		{
			AWGCharacter* Character = Cast<AWGCharacter>(Actor);
			if (Character)
			{
				Character->TakeDamage(ExplosionDamage);
			}
			
		}
	}
	
	
	GetWorldTimerManager().SetTimer(RedColorTimerHandle, this, &Atrap_platform::ResetMaterial, MaterialResetTime, false);

	if(CollisionComp->IsOverlappingActor(OtherActor) && bIsTrapCooldown == false)
		{
		UE_LOG(LogTemp, Warning, TEXT("Calling ExplodePrepare cause trap overlapping actor"));
			auto Lambda = [this, OtherActor]()
			{
				ExplodePrepare(OtherActor);
			};
			
			GetWorldTimerManager().SetTimer(ExplodeCooldownHandle, Lambda, 0, true);
		}
	
}

inline void Atrap_platform::ResetMaterial()
{
	UMaterialInterface* MatChange = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial'"));
	if (MatChange)
	{
		Platform->SetMaterial(0, MatChange);
	}
}

void Atrap_platform::SetTrapCooldown(AActor* OtherActor)
{
	bIsTrapCooldown = true;
	
	auto Lambda = [this, OtherActor]()
	{
		ResetTrapCooldown(OtherActor);
	};
	
	GetWorldTimerManager().SetTimer(CooldownHandle, Lambda,CooldownDuration, false);
}

void Atrap_platform::ResetTrapCooldown(AActor* OtherActor)
{
	bIsTrapCooldown = false;

	if (CollisionComp->IsOverlappingActor(OtherActor))
	{
		ExplodePrepare(OtherActor);
		SetTrapCooldown(OtherActor); 
	}
}

void Atrap_platform::Wind(AActor* OtherActor)
{
	UMaterialInterface* MatChange = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/LevelPrototyping/Materials/MI_Solid_Blue.MI_Solid_Blue'"));
	if(MatChange){
		Platform->SetMaterial(0, MatChange);
	}
	auto WindApplyLambda = [this, OtherActor]()
	{
		WindApply(OtherActor);
	};
	GetWorldTimerManager().SetTimer(WindChangeHandle,WindApplyLambda,WindChangeRate,true, 0.f);
}

void Atrap_platform::WindApply(AActor* OtherActor)
{
	float BetterRandomDirection =  FMath::RandRange(MinYStrenght,MaxYStrenght);
	if (BetterRandomDirection > 0)
	{
		BetterRandomDirection += 30.f;
	}
	else
	{
		BetterRandomDirection -= 30.f;
	}
	
	FVector WindDirection = FVector(0.f, BetterRandomDirection, 0.f);
	auto WindChangeLambda = [this, OtherActor, WindDirection]()
	{
		WindChange(OtherActor,WindDirection);
	};
	GetWorldTimerManager().ClearTimer(WindTimerHandle);
	GetWorldTimerManager().SetTimer(WindTimerHandle,WindChangeLambda,WindPressure*GetWorld()->GetDeltaSeconds(),true);
	
}

void Atrap_platform::WindChange(AActor* OtherActor, FVector WindDirection)
{
	
	FVector TargetLocation = OtherActor->GetActorLocation() + WindDirection;
	FVector newLocation = FMath::VInterpTo(OtherActor->GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), WindInterpSpeed);
	OtherActor->SetActorLocation(newLocation);
}



