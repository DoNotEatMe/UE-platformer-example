// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBaseComponent.h"
#include "Trap_Jump_comp.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WG_API UTrap_Jump_comp : public UTrapBaseComponent
{
	GENERATED_BODY()

public:
	UTrap_Jump_comp();
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Jump")
	float JumpPower = 1000.f;
	UFUNCTION()
	void JumpActivate(AActor* OtherActor);
	UFUNCTION()
	void JumpDeactivate(AActor* OtherActor);
	UPROPERTY()
	float DefaultJump;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	virtual void BeginPlay() override;
	
};
