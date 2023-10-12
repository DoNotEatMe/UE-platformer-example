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
                TArray<AActor*> TrapActors;
                UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATrapBase::StaticClass(), TrapActors);
                
                for (AActor* TrapActor : TrapActors)
                {
                    UTrap_MovingPlatform_comp* MovingTrap = Cast<UTrap_MovingPlatform_comp>(TrapActor->GetComponentByClass(UTrap_MovingPlatform_comp::StaticClass()));
                    if (MovingTrap)
                    {
                      MovingTrap->MovingPlatform();
                        continue;
                    }

                    UTrap_Hiding_comp* HidingTrap = Cast<UTrap_Hiding_comp>(TrapActor->GetComponentByClass(UTrap_Hiding_comp::StaticClass()));
                    if (HidingTrap)
                    {
                        HidingTrap->HidingTrap();
                        continue;
                    }
                }
                
                OnStart.Broadcast(UGameplayStatics::GetRealTimeSeconds(GetWorld()));
                bTriggerActivated = true;
                
            }
            return;
        }
    }
}






