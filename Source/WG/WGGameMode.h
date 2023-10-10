// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WGGameMode.generated.h"


UCLASS(minimalapi)
class AWGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWGGameMode();
	
	UFUNCTION(BlueprintCallable)
	void GameOver(bool bWonGame);

	UPROPERTY(BlueprintReadOnly)
	double GameStartTime;

	UPROPERTY(BlueprintReadOnly)
	double GameEndTime;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UGameOver> GameOverHUDClass;

	UPROPERTY()
	class UGameOver* GameOverHUD;

	virtual void ResetLevel() override;

	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

	void DeleteHUD();


protected:
	virtual void BeginPlay() override;
};



