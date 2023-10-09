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

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameOver> GameOverHUDClass;

	UPROPERTY()
	class UGameOver* GameOverHUD;

};



