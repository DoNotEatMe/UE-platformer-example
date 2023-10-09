// Fill out your copyright notice in the Description page of Project Settings.


#include "trigger.h"

#include "WGGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h" 
#include "GameFramework/Character.h" 


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
        UE_LOG(LogTemp,Warning,TEXT("start: %f"), GameMode->GameStartTime);
        
        if (GameMode && !bTriggerActivated)
        {
            
            UE_LOG(LogTemp,Warning,TEXT("activated: %hhd"), bTriggerActivated);
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






