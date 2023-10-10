// Fill out your copyright notice in the Description page of Project Settings.


#include "trigger.h"

#include "WGGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h" 
#include "GameFramework/Character.h"
#include "trap_platform.h"


Atrigger::Atrigger()
{
    GameMode = nullptr;
    
}

void Atrigger::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddDynamic(this, &Atrigger::OnOverlapBegin);
    GameMode = Cast<AWGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
}

void Atrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{

    if (this->ActorHasTag("Win")){
        SetOver(OtherActor, true);
        return;
    }

    if (this->ActorHasTag("Lose"))
    {
        SetOver(OtherActor, false);
        
        return;
    }
    
    if (this->ActorHasTag("Start"))
    {
        
        if (GameMode && !bTriggerActivated)
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
                }
            }
            
            GameMode->GameStartTime =  UGameplayStatics::GetRealTimeSeconds(GetWorld());
            bTriggerActivated = true;
            
        }
        return;
    }
}

void Atrigger::SetOver(AActor* OtherActor, bool bWon)
{
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
    if (OtherActor == PlayerCharacter && OtherActor != this)
    {
        if (GameMode){
            GameMode->GameOver(bWon);
        }
    }
}






