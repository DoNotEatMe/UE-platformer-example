// Copyright Epic Games, Inc. All Rights Reserved.

#include "WGGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameOver.h"
#include "Blueprint/UserWidget.h"
#include "gameHUD.h"



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

		PlayerController->SetInputMode(FInputModeUIOnly());

		GameEndTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
		if (GameOverHUDClass)
		{
			GameOverHUD = CreateWidget<UGameOver>(GetWorld(),GameOverHUDClass);
			check(GameOverHUD);

			UGameplayStatics::SetGamePaused(GetWorld(),true);
			GameOverHUD->AddToPlayerScreen();
			
			GameOverHUD->SetGameDuration(GameStartTime,GameEndTime);
			GameOverHUD->SetWinLose(bWonGame);



			
			
			
		}
		
	}

	
	
}

void AWGGameMode::ResetLevel()
{
	Super::ResetLevel();
}

void AWGGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
}

void AWGGameMode::DeleteHUD()
{
	GameOverHUD->SetVisibility(ESlateVisibility::Hidden);

}

void AWGGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	
}





