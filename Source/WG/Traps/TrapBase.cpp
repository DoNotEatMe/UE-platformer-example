#include "TrapBase.h"
#include "Trap_Explosive_comp.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ATrapBase::ATrapBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>("Platform");
	RootComponent = Platform;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/Cube.Cube'"));
	if (MeshAsset.Succeeded())
	{
		Platform->SetStaticMesh(MeshAsset.Object);
		Platform->SetRelativeScale3D(FVector(3.f,3.f,0.1f));
	}
	
	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Interact Collision");
	CollisionComp->SetupAttachment(Platform);
	CollisionComp->SetRelativeLocation(FVector(0.0f,0.0f,70.0f));
	CollisionComp->SetBoxExtent(FVector(50.0f,50.0f,20.0f));
}

void ATrapBase::BeginPlay()
{
	Super::BeginPlay();
	DynamicMaterial = UMaterialInstanceDynamic::Create(Platform->GetMaterial(0),this);
	Platform->SetMaterial(0,DynamicMaterial);
	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::Gray);
}

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
