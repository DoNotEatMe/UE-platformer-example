// Copyright Epic Games, Inc. All Rights Reserved.

#include "WGGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameOver.h"
#include "gameHUD.h"
#include "Blueprint/UserWidget.h"



AWGGameMode::AWGGameMode()
{
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameOverHUDClass = nullptr;
	GameOverHUD = nullptr;


	
}


void AWGGameMode::GameOver(bool bWonGame)
{

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;

		PlayerController->SetInputMode(FInputModeGameAndUI());

		GameEndTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		UE_LOG(LogTemp,Warning,TEXT("start: %f"), GameStartTime);
		UE_LOG(LogTemp,Warning,TEXT("end: %f"), GameEndTime);
		if (GameOverHUDClass)
		{
			GameOverHUD = CreateWidget<UGameOver>(GetWorld(),GameOverHUDClass);
			check(GameOverHUD);

			
			GameOverHUD->AddToPlayerScreen();
			UGameplayStatics::SetGamePaused(GetWorld(),true);
			GameOverHUD->SetGameDuration(GameStartTime,GameEndTime);
			GameOverHUD->SetWinLose(bWonGame);
			
		}
		
	}

	
	
}





