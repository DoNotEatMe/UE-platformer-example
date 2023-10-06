// Fill out your copyright notice in the Description page of Project Settings.


#include "WinTrigger.h"


AWinTrigger::AWinTrigger()
{
}

void AWinTrigger::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("Win volume here"));
}


void AWinTrigger::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if()
	
}


