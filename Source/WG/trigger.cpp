#include "trigger.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h" 
#include "WGCharacter.h"
#include "Traps/Trap_Hiding_comp.h"
#include "WG/Traps/TrapBase.h"
#include "WG/Traps/Trap_MovingPlatform_comp.h"

Atrigger::Atrigger()
{
}

void Atrigger::BeginPlay()
{
    Super::BeginPlay();
    OnActorBeginOverlap.AddDynamic(this, &Atrigger::OnOverlapBegin);
}

void Atrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    AWGCharacter* Player = Cast<AWGCharacter>(Controller->GetPawn());

    if (Player && Player == OtherActor){
    
        if (this->ActorHasTag("Win")){
            OnGameOver.Broadcast(true);
            return;
        }

        if (this->ActorHasTag("Lose"))
        {
            OnGameOver.Broadcast(false);
            return;
        }
        
        if (this->ActorHasTag("Start"))
        {
            
            if (!bTriggerActivated)
            {
                TrapsStart.Broadcast();
                OnStart.Broadcast(UGameplayStatics::GetRealTimeSeconds(GetWorld()));
                bTriggerActivated = true;
            }
            return;
        }
    }
}






