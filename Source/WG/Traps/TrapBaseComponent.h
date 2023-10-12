#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrapBaseComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WG_API UTrapBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTrapBaseComponent();


	UPROPERTY()
	class ATrapBase* OwnerActor;
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY()
	class UBoxComponent* InteractCollision;

	UFUNCTION()
	virtual void ResetTimer() {}	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
};
