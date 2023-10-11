// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "trap_platform.generated.h"

UCLASS()
class WG_API Atrap_platform : public AActor
{
	GENERATED_BODY()
	
public:	
	Atrap_platform();

	UPROPERTY(VisibleAnywhere, Category="Components", meta = (AllowPrivateAccess=true), BlueprintReadOnly)
	UStaticMeshComponent* Platform;

	UPROPERTY(VisibleAnywhere, Category="Components", meta = (AllowPrivateAccess=true), BlueprintReadOnly)
	class UBoxComponent* CollisionComp;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	
private:

	//general
	FTimerHandle CooldownHandle;
	UFUNCTION()
	void ResetMaterial();
	UFUNCTION()
	void SetTrapCooldown(AActor* OtherActor);
	UFUNCTION()
	void ResetTrapCooldown(AActor* OtherActor);
	UPROPERTY(EditAnywhere, Category="Traps Settings|General")
	float CooldownDuration = 6.f;
	UPROPERTY(VisibleAnywhere, Category="Traps Settings|General")
	bool bIsTrapCooldown;
	
	//Explosion Setup
	FTimerHandle ExplodeTimerHandle;
	FTimerHandle RedColorTimerHandle;
	FTimerHandle ExplodeCooldownHandle;
	UFUNCTION()
	void ExplodePrepare(AActor* OtherActor);
	UFUNCTION()
	void Explode(AActor* OtherActor);
	UPROPERTY(EditAnywhere, Category="Traps Settings|Explode")
	float MaterialResetTime = 0.3f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Explode")
	float ExplodeTime = 1.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Explode")
	float ExplosionDamage = 10.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Explode") 
	float TrapDamage = 50.f;
	
	//Wind Setup
	FTimerHandle WindTimerHandle;
	FTimerHandle WindChangeHandle;
	UFUNCTION()
	void Wind(AActor* OtherActor);
	UFUNCTION()
	void WindApply(AActor* OtherActor);
	UFUNCTION()
	void WindChange(AActor* OtherActor,FVector WindDirection);
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float WindChangeRate = 2.f;
	UPROPERTY(VisibleAnywhere, Category="Traps Settings|Wind")
	bool bWindRight;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float WindPressure = 1.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float WindInterpSpeed = 1.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float MinYStrenght = -100.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Wind")
	float MaxYStrenght = 100.f;


	//Shake Setup
	FTimerHandle ShakeHandler;
	UPROPERTY()
	bool bIsShaking;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	float ShakeDuration = 5.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	float ShakeIntensity = 1.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	float RedFlagTime = 1.f;
	UPROPERTY()
	FRotator InitialRotation;
	UFUNCTION()
	void ShakePrepare();
	UFUNCTION()
	void Shake();

	//JumpTrap
	UPROPERTY(EditAnywhere, Category="Traps Settings|Jump")
	float JumpPower = 1000.f;
	UFUNCTION()
	void JumpActivate(AActor* OtherActor);
	UFUNCTION()
    void JumpDeactivate(AActor* OtherActor);
	UPROPERTY()
	float DefaultJump;
	
	

public:
	
	
	//Moving platform
	FTimerHandle PlatformMovingHandle;
	UPROPERTY(VisibleAnywhere, Category="Traps Settings|Moving Platform")
	FVector MoveStartLocation;
	UPROPERTY(VisibleAnywhere, Category="Traps Settings|Moving Platform")
	FVector MoveEndLocation;
	UPROPERTY(VisibleAnywhere,Category="Traps Settings|Moving Platform")
	bool bEnd;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Moving Platform")
	float MoveRate = 1.f;
	UPROPERTY(EditAnywhere,Category="Traps Settings|Moving Platform" )
	float PlatformVelocityInSec= 5.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Moving Platform")
	float FirstTimeDelay = 0;
	UFUNCTION()
	void MovingPlatform();
	UFUNCTION()
	void MoveObject();

	//Hidding Trap
	FTimerHandle HidingTrapHandler;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Hide/Unhide")
	float HidingRate = 10.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Hide/Unhide")
	float StartHiding = 3.f;
	UFUNCTION()
	void HidingTrap();
	UFUNCTION()
	void HideUnhide();

	
	

	//Timers Reset for OpenLevel()
	UFUNCTION()
	void ResetAllTimers();
	
};


