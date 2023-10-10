// Fill out your copyright notice in the Description page of Project Settings.


#include "trap_platform.h"

#include "Components/BoxComponent.h"
#include "WGCharacter.h"

#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"



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

void Atrap_platform::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &Atrap_platform::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &Atrap_platform::OnOverlapEnd);
}

void Atrap_platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void Atrap_platform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if(this->ActorHasTag("Explode")){
		if (bIsTrapCooldown == false){
			ExplodePrepare(OtherActor);
			SetTrapCooldown(OtherActor);
		}
		return;
	}
	if(this->ActorHasTag("Wind")){
		Wind(OtherActor);
		return;
	}
	if (this->ActorHasTag("Shake"))
	{
		
		ShakePrepare();
	}
	
}

void Atrap_platform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(this->ActorHasTag("Wind")){
		GetWorldTimerManager().ClearTimer(WindTimerHandle);
		GetWorldTimerManager().ClearTimer(WindChangeHandle);
		ResetMaterial();
	}
	
}

//Explosive trap

void Atrap_platform::ExplodePrepare(AActor* OtherActor)
{
	if(CollisionComp->IsOverlappingActor(OtherActor)){
		
		UMaterialInterface* MatChange = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/LevelPrototyping/Materials/OrangeExplode.OrangeExplode'"));

		if(MatChange){
			Platform->SetMaterial(0, MatChange);
		}
		
		auto Lambda = [this, OtherActor]()
		{
			Explode(OtherActor);
		};
		
		GetWorldTimerManager().SetTimer(ExplodeTimerHandle, Lambda, ExplodeTime, false);
	
	}
}

void Atrap_platform::Explode(AActor* OtherActor)
{
	UMaterialInterface* MatChange = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/LevelPrototyping/Materials/RedBlink.RedBlink'"));
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
		UE_LOG(LogTemp, Warning, TEXT("Calling ExplodePrepare in case of trap overlapping actor"));
			auto Lambda = [this, OtherActor]()
			{
				ExplodePrepare(OtherActor);
			};
			
			GetWorldTimerManager().SetTimer(ExplodeCooldownHandle, Lambda, 0, true);
		}
	
}

inline void Atrap_platform::ResetMaterial()
{
	UMaterialInterface* MatChange = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/LevelPrototyping/Materials/Platform.Platform'"));
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

	if (OtherActor && OtherActor->IsA<AWGCharacter>() && CollisionComp->IsOverlappingActor(OtherActor))
	{
		ExplodePrepare(OtherActor);
		SetTrapCooldown(OtherActor); 
	}
}

//Wind Trap

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

	// Not sure i need VInterpTo. May be just velocity*deltatime?
	// But as player, filling wind better. 
	FVector newLocation = FMath::VInterpTo(OtherActor->GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), WindInterpSpeed);
	OtherActor->SetActorLocation(newLocation);
}


//Moving Trap

void Atrap_platform::MovingPlatform()
{
	MoveStartLocation = this->GetActorLocation();
	MoveEndLocation = CollisionComp->GetComponentLocation();
	bEnd = false;
	
	GetWorld()->GetTimerManager().SetTimer(PlatformMovingHandle,this, &Atrap_platform::MoveObject, MoveRate*GetWorld()->GetDeltaSeconds() ,true,FirstTimeDelay);
}

void Atrap_platform::MoveObject()
{
	
	FVector CurrentLocation;
	FVector TargetLocation;
	
	if (!bEnd)
	{
		CurrentLocation = this->GetActorLocation();
		TargetLocation = CurrentLocation + (FVector(MoveEndLocation.X - MoveStartLocation.X, MoveEndLocation.Y - MoveStartLocation.Y,MoveEndLocation.Z - MoveStartLocation.Z)/PlatformVelocityInSec) * GetWorld()->GetDeltaSeconds();

		if (CurrentLocation.Equals(MoveEndLocation, 3.f))
		{
			bEnd = !bEnd;
		}
	}
	if (bEnd)
	{
		CurrentLocation = this->GetActorLocation();
		TargetLocation = CurrentLocation + (FVector(MoveStartLocation.X - MoveEndLocation.X, MoveStartLocation.Y - MoveEndLocation.Y,MoveStartLocation.Z - MoveEndLocation.Z)/PlatformVelocityInSec) * GetWorld()->GetDeltaSeconds();
		if (CurrentLocation.Equals(MoveStartLocation, 3.f))
		{
			bEnd = !bEnd;
		}
	}
	
	this->SetActorLocation(TargetLocation);
}



//Shake Trap

void Atrap_platform::ShakePrepare()
{
	UMaterialInterface* MatChange = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/LevelPrototyping/Materials/OrangeExplode.OrangeExplode'"));
	if (MatChange)
	{
		Platform->SetMaterial(0, MatChange);
	}

	bIsShaking = true;
	
	InitialRotation = GetActorRotation();
	
	GetWorld()->GetTimerManager().SetTimer(ShakeHandler,this, &Atrap_platform::Shake, 0.05, true);
}

void Atrap_platform::Shake()
{
	FRotator ShakeDelta(
		0,
		0,
		FMath::RandRange(-ShakeIntensity,ShakeIntensity)
		);

	SetActorRotation(InitialRotation + ShakeDelta);
		
	ShakeDuration -= 0.05f;

		if (ShakeDuration <= RedFlagTime)
		{
			UMaterialInterface* MatChange = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/LevelPrototyping/Materials/RedBlink.RedBlink'"));
			if (MatChange)
			{
				Platform->SetMaterial(0, MatChange);
			}

		}

	if (ShakeDuration <= 0)
	{
		SetActorRotation(InitialRotation);
		AActor* Actor = Cast<AActor>(this);
		if (Actor)
		{
			UPrimitiveComponent* MyRootComponent = Actor->FindComponentByClass<UPrimitiveComponent>();
			if (MyRootComponent)
			{
				MyRootComponent->SetSimulatePhysics(true);
				MyRootComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
			}
		}
	}
}



void Atrap_platform::ResetAllTimers()
{
	GetWorld()->GetTimerManager().ClearTimer(CooldownHandle);
	GetWorld()->GetTimerManager().ClearTimer(ExplodeTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(RedColorTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ExplodeCooldownHandle);
	GetWorld()->GetTimerManager().ClearTimer(WindTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(WindChangeHandle);
	GetWorld()->GetTimerManager().ClearTimer(ShakeHandler);
	GetWorld()->GetTimerManager().ClearTimer(PlatformMovingHandle);
}
	


