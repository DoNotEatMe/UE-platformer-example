#pragma once

#include "CoreMinimal.h"
#include "TrapBaseComponent.h"
#include "Trap_Hiding_comp.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WG_API UTrap_Hiding_comp : public UTrapBaseComponent
{
	GENERATED_BODY()

public:
	UTrap_Hiding_comp();

	FTimerHandle HidingTrapHandler;
	
	UPROPERTY(EditAnywhere, Category="Traps Settings|Hide/Unhide")
	float HidingRate = 10.f;
	UPROPERTY(EditAnywhere, Category="Traps Settings|Hide/Unhide")
	float StartDelay = 3.f;

	UFUNCTION()
	void HidingTrap();
	UFUNCTION()
	void HideUnhide();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
};
