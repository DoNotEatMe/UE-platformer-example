// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "WinTrigger.generated.h"

/**
 * 
 */
UCLASS()
class WG_API AWinTrigger : public ATriggerVolume
{
	GENERATED_BODY()

public:
	AWinTrigger();
	virtual void Tick(float DeltaSeconds) override;
	
	
protected:
	virtual void BeginPlay() override;
	
	
};
