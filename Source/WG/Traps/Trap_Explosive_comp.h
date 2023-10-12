// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrapBaseComponent.h"
#include "Engine/DamageEvents.h"
#include "Trap_Explosive_comp.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDamageExplosiveTrapCompDelegate, float, DamageDealt, AActor*, Trap,
                                               FDamageEvent&, DamageEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WG_API UTrap_Explosive_comp : public UTrapBaseComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrap_Explosive_comp();

	UPROPERTY()
	FDamageExplosiveTrapCompDelegate OnApplyDamage;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
private:

	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	

	
	
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
	
	FTimerHandle ExplodeTimerHandle;
	FTimerHandle RedColorTimerHandle;
	FTimerHandle ExplodeCooldownHandle;
	FTimerHandle CooldownHandle;
	UFUNCTION()
	void ExplodePrepare(AActor* OtherActor);
	UFUNCTION()
	void Explode(AActor* OtherActor);
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Explode")
	float TimeForExplosion = 1.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Explode")
	float MaterialResetTime = 0.3f;
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Explode") 
	float TrapDamage = 50.f;

	UFUNCTION()
	virtual  void ResetTimer();
	
	
		
};
