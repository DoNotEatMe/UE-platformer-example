#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "trigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameStartTriggerDelegate, double, GameStartTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameOverTriggerDelegate, bool, bWinLose);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTrapsStartDelegate);

UCLASS()
class WG_API Atrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	Atrigger();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
	UPROPERTY()
	bool bTriggerActivated;

	UPROPERTY(BlueprintCallable)
	FGameOverTriggerDelegate OnGameOver;
	UPROPERTY(BlueprintCallable)
	FGameStartTriggerDelegate OnStart;
	UPROPERTY(Blueprintable)
	FTrapsStartDelegate TrapsStart;

protected:
	virtual void BeginPlay() override;
};
