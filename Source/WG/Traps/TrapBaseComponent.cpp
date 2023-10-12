// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapBaseComponent.h"
#include "TrapBase.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UTrapBaseComponent::UTrapBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OwnerActor = nullptr;
	DynamicMaterial = nullptr;
	InteractCollision = nullptr;
}


// Called when the game starts
void UTrapBaseComponent::BeginPlay()
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
		InteractCollision->OnComponentBeginOverlap.AddDynamic(this, &UTrapBaseComponent::OnOverlapBegin);
		InteractCollision->OnComponentEndOverlap.AddDynamic(this, &UTrapBaseComponent::OnOverlapEnd);
	} else
	{
		UE_LOG(LogTemp,Error,TEXT("InteractCollision lost at %s --TrapBaseComponent"), *this->GetOwner()->GetName());
	}
	
}


// Called every frame
void UTrapBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTrapBaseComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	
}

void UTrapBaseComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

