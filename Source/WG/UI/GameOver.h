#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

UCLASS()
class WG_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UTextBlock* WinLose;
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* Duration;

	UFUNCTION(BlueprintCallable)
	void RestartLevel();
	UFUNCTION()
	void SetGameDuration (double GameStarTime, double GameEndtime);
	UFUNCTION()
	void SetWinLose(bool bWin);
};
