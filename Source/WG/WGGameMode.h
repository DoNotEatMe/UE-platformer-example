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

	UFUNCTION()
	void SetGameStartTime(double time);

	UPROPERTY(BlueprintReadOnly)
	double GameEndTime;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UgameHUD> PlayerHUDClass;
	UPROPERTY()
	UgameHUD* PlayerHUD;
	

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<class UGameOver> GameOverHUDClass;
	UPROPERTY()
	UGameOver* GameOverHUD;
	
	void DeleteHUD();

protected:
	virtual void BeginPlay() override;

};





