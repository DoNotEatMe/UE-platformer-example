#pragma once

#include "CoreMinimal.h"
#include "TrapBaseComponent.h"
#include "Trap_Shake_comp.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WG_API UTrap_Shake_comp : public UTrapBaseComponent
{
	GENERATED_BODY()
public:
	
	UTrap_Shake_comp();
	
	FTimerHandle ShakeHandler;
	FTimerHandle DestroyHandler;
	
	UPROPERTY()
	bool bIsShaking;
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	float ShakeDuration = 5.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	float ShakeIntensity = 5.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Shake")
	float RedFlagDuration = 1.f;
	UPROPERTY()
	FRotator InitialRotation;

	UFUNCTION()
	void ShakePrepare();
	UFUNCTION()
	void Shake();

	UFUNCTION()
	void SelfDestroy();
	
	virtual void ResetTimer() override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	virtual void BeginPlay() override;
};


