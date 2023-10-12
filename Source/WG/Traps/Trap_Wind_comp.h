// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBaseComponent.h"
#include "Trap_Wind_comp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WG_API UTrap_Wind_comp : public UTrapBaseComponent
{
	GENERATED_BODY()

public:

	UTrap_Wind_comp();
	
	//Wind Setup
	FTimerHandle WindTimerHandle;
	FTimerHandle WindChangeHandle;
	
	UFUNCTION()
	void Wind(AActor* OtherActor);
	UFUNCTION()
	void WindApply(AActor* OtherActor);
	UFUNCTION()
	void WindChange(AActor* OtherActor,FVector WindDirection);
	// How often Wind Change Direction
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float WindChangeRate = 2.f;
	UPROPERTY()
	bool bWindRight;
	
	//WindPressure*GetWorld()->GetDeltaSeconds() as additional option to rule power in WindApply timer
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float WindPressure = 1.f;

	//Default range N -30 30 N to set power
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float MinYAxisPower = -100.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float MaxYAxisPower = 100.f;

	//Minimum wind power
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float MinWindPower = 30.f;
	

	
virtual void ResetTimer() override;
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	 

protected:
	virtual void BeginPlay() override;
	
};
