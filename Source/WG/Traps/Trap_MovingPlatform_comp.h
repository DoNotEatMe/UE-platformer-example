// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBaseComponent.h"
#include "Trap_MovingPlatform_comp.generated.h"

DECLARE_DYNAMIC_DELEGATE(FTriggerMovingPlatformHandle);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WG_API UTrap_MovingPlatform_comp : public UTrapBaseComponent
{
	GENERATED_BODY()

public:
	UTrap_MovingPlatform_comp();

	FTimerHandle TransitionHandle;
	
	UPROPERTY(VisibleAnywhere, Category="Traps Settings|Moving Platform")
	FVector StartPoint;
	UPROPERTY(VisibleAnywhere, Category="Traps Settings|Moving Platform")
	FVector EndPoint;
	
	UPROPERTY()
	bool bEnd;
	
	// Time in seconds for one way (Start->End)
	UPROPERTY(EditAnywhere,Category="Traps Settings|Moving Platform" )
	float PlatformVelocityInSec= 5.f;
	// Seconds before start moving (after was triggered)
	UPROPERTY(EditAnywhere, Category="Traps Settings|Moving Platform")
	float FirstTimeDelay = 1;
	
	UFUNCTION()
	void MovingPlatform();
	UFUNCTION()
	void MoveObject();

	UPROPERTY()
	FTriggerMovingPlatformHandle OnStartTrigger;

	virtual void ResetTimer() override;


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	
};
