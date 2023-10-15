// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamagePop.generated.h"

/**
 * 
 */
UCLASS()
class WG_API UDamagePop : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* Damage;

	UFUNCTION()
	void DamagePop(float DamageAmount, APlayerController* PlayerController,UWidgetComponent* WidgetComponent );

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FloatUpAnimation     = nullptr;

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
