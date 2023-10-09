// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UGameOver::RestartLevel()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;

		PlayerController->SetInputMode(FInputModeGameOnly());

		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
	}
	
}

void UGameOver::SetGameDuration(double GameStarTime, double GameEndtime)
{
	double DurationCount = GameEndtime - GameStarTime;
	Duration->SetText(FText::Format(FText::FromString("{0}{1}"),FText::FromString(TEXT("Your Run time is: ")),FText::AsNumber(DurationCount)));
	
}

void UGameOver::SetWinLose(bool bWin)
{
	if (bWin)
	{
		WinLose->SetText(FText::FromString(TEXT("YOU WON!!!")));
	}
	if (!bWin)
	{
		WinLose->SetText((FText::FromString(TEXT("YOU LOSE :C"))));
	}
}
