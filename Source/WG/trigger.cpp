// Fill out your copyright notice in the Description page of Project Settings.


#include "trigger.h"

#include "WGGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h" 
#include "GameFramework/Character.h"
#include "trap_platform.h"
#include "WGCharacter.h"


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
                TArray<AActor*> TrapArray;
                UGameplayStatics::GetAllActorsOfClass(GetWorld(),Atrap_platform::StaticClass(),TrapArray);
                for (AActor* Actor : TrapArray)
                {
                    Atrap_platform* TrapPlatform = Cast<Atrap_platform>(Actor);
                    if (TrapPlatform)
                    {
                        if (TrapPlatform->ActorHasTag("Moving"))
                        {
                            TrapPlatform->MovingPlatform();
                        }
                        if (TrapPlatform->ActorHasTag("Hiding"))
                        {
                            TrapPlatform->HidingTrap();
                        }
                        
                    }
                }
                
                OnStart.Broadcast(UGameplayStatics::GetRealTimeSeconds(GetWorld()));
                bTriggerActivated = true;
                
            }
            return;
        }
    }
}






