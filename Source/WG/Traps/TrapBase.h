#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapBase.generated.h"

UCLASS()
class WG_API ATrapBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrapBase();

	UPROPERTY(VisibleAnywhere, Category="CPP|Components", meta = (AllowPrivateAccess=true), BlueprintReadOnly)
	UStaticMeshComponent* Platform;
	UPROPERTY(VisibleAnywhere, Category="CPP|Components", meta = (AllowPrivateAccess=true), BlueprintReadOnly)
	class UBoxComponent* CollisionComp;
	
	UFUNCTION(BlueprintCallable, Category="CPP|Components")
	void ChangeMaterialColor(FLinearColor color);

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

	UFUNCTION()
	void ResetTimers();
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
};
