// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapBase.h"

#include "Trap_Explosive_comp.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATrapBase::ATrapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Platform = CreateDefaultSubobject<UStaticMeshComponent>("Platform");
	RootComponent = Platform;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube_WMatExample.SM_Cube_WMatExample'"));
	if (MeshAsset.Succeeded())
	{
		Platform->SetStaticMesh(MeshAsset.Object);
		Platform->SetRelativeScale3D(FVector(3.f,3.f,0.1f));
	}
	
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Interact Collision");
	CollisionComp->SetupAttachment(Platform);
	CollisionComp->SetRelativeLocation(FVector(50.0f,50.0f,120.0f));
	CollisionComp->SetBoxExtent(FVector(50.0f,50.0f,20.0f));

	
	
}



// Called when the game starts or when spawned
void ATrapBase::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp,Error,TEXT("reset %s"),*Platform->GetMaterial(0)->GetName());
	DynamicMaterial = UMaterialInstanceDynamic::Create(Platform->GetMaterial(0),this);
	Platform->SetMaterial(0,DynamicMaterial);
	
	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::Gray);
	
	
}

// Called every frame
void ATrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapBase::ChangeMaterialColor(FLinearColor color)
{
	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), color);
}

void ATrapBase::ResetTimers()
{
	TArray<UTrapBaseComponent*> Components;
	GetComponents<UTrapBaseComponent>(Components);
	for (UTrapBaseComponent* Comp : Components)
	{
		Comp->ResetTimer();
	}
}
