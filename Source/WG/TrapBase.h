// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapBase.generated.h"

UCLASS()
class WG_API ATrapBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
