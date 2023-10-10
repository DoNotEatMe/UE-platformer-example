// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

/**
 * 
 */
UCLASS()
class WG_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

public:

	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* WinLose;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* Duration;

	UFUNCTION(BlueprintCallable)
	void RestartLevel();

	UFUNCTION(BlueprintCallable)
	void ResetLevelFromUI();

	UFUNCTION(BlueprintCallable)
	void ResetPlayerFromUI(AController* NewPlayer, AActor* StartSpot);

	UFUNCTION()
	void SetGameDuration (double GameStarTime, double GameEndtime);

	UFUNCTION()
	void SetWinLose(bool bWin);
};
