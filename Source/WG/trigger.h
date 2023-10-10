// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "trigger.generated.h"


class Atrap_platform;
class AWGGameMode;
/**
 * 
 */
UCLASS()
class WG_API Atrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	Atrigger();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void SetOver(AActor* OtherActor, bool bWon);

	UPROPERTY()
	bool bTriggerActivated;

	UPROPERTY()
	AWGGameMode* GameMode;
	
private:

};
