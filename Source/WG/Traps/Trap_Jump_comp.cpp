#include "Trap_Jump_comp.h"
#include "WG/WGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UTrap_Jump_comp::UTrap_Jump_comp()
{
}

void UTrap_Jump_comp::BeginPlay()
{
	Super::BeginPlay();
	AWGCharacter* Character = Cast<AWGCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (Character)
	{
		UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
		DefaultJump = Movement->JumpZVelocity;
	}
}

void UTrap_Jump_comp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTrap_Jump_comp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	JumpActivate(OtherActor);
}

void UTrap_Jump_comp::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	JumpDeactivate(OtherActor);
}


void UTrap_Jump_comp::JumpActivate(AActor* OtherActor)
{
	AWGCharacter* Character = Cast<AWGCharacter>(OtherActor);
	if (Character)
	{
		UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
		Movement->JumpZVelocity = JumpPower;
	}
}

void UTrap_Jump_comp::JumpDeactivate(AActor* OtherActor)
{
	AWGCharacter* Character = Cast<AWGCharacter>(OtherActor);
	if (Character)
	{
		UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
		Movement->JumpZVelocity = DefaultJump;
	}
	
}

