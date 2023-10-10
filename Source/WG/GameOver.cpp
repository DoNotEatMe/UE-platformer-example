// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"

#include "trap_platform.h"
#include "WGGameMode.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "trigger.h"



void UGameOver::RestartLevel()
{
	AWGGameMode* GameMode = Cast<AWGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PlayerController && GameMode)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;
		PlayerController->SetInputMode(FInputModeGameOnly());

		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),Atrap_platform::StaticClass(),Actors);
		for (AActor* Actor: Actors)
		{
			Atrap_platform* Trap = Cast<Atrap_platform>(Actor);
			if (Trap)
			{
				Trap->ResetAllTimers();
			}
		}
		UGameplayStatics::OpenLevel(GetWorld(), *GetWorld()->GetName(), false);


		
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("ResetLevel() in GameOver.cpp error finding playercontroller/gamemode "));
	}
	
	
}

void UGameOver::ResetLevelFromUI()
{
	AWGGameMode* GameMode = Cast<AWGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->ResetLevel();
	
}

void UGameOver::ResetPlayerFromUI(AController* NewPlayer, AActor* StartSpot)
{
	AWGGameMode* GameMode = Cast<AWGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
	
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
