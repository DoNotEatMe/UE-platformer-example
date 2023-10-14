#pragma once

#include "CoreMinimal.h"
#include "TrapBaseComponent.h"
#include "Trap_Explosive_comp.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WG_API UTrap_Explosive_comp : public UTrapBaseComponent
{
	GENERATED_BODY()

public:	
	UTrap_Explosive_comp();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void ResetMaterial();
	UFUNCTION()
	void SetTrapCooldown(AActor* OtherActor);
	UFUNCTION()
	void ResetTrapCooldown(AActor* OtherActor);
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Explode")
	float CooldownDuration = 6.f;
	UPROPERTY(VisibleAnywhere, Category="Traps Settings|Explode")
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
	
	virtual  void ResetTimer()  override;


protected:
	virtual void BeginPlay() override;
	
		
};
