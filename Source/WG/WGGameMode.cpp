#include "WGGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "WG/UI/GameOver.h"
#include "Blueprint/UserWidget.h"
#include "WG/UI/gameHUD.h"
#include "WGCharacter.h"
#include "trigger.h"

AWGGameMode::AWGGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;
	
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

void AWGGameMode::SetGameStartTime(double time)
{
	GameStartTime = time;
}

void AWGGameMode::DeleteHUD()
{
	GameOverHUD->SetVisibility(ESlateVisibility::Hidden);
}

void AWGGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller)
	{
		AWGCharacter* Player = Cast<AWGCharacter>(Controller->GetPawn());
		if (Player)
		{
			Player->OnGameOver.AddDynamic(this,&AWGGameMode::GameOver);
		}
	}

	TArray<AActor*> Triggers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),Atrigger::StaticClass(),Triggers);
	for (AActor* Actor : Triggers)
	{
		Atrigger* Trigger = Cast<Atrigger>(Actor);
		if(Trigger && Trigger->ActorHasTag("Win") || Trigger->ActorHasTag("Lose"))
		{
			Trigger->OnGameOver.AddDynamic(this,&AWGGameMode::GameOver);
		}
		else if (Trigger && Trigger->ActorHasTag("Start"))
		{
			Trigger->OnStart.AddDynamic(this,&AWGGameMode::SetGameStartTime);
		}
	}

	if(PlayerHUDClass)
	{
		APlayerController* FPC = UGameplayStatics::GetPlayerController(GetWorld(),0);
		check(FPC);
		PlayerHUD = CreateWidget<UgameHUD>(FPC, PlayerHUDClass);
		check(PlayerHUD);
		PlayerHUD->AddToPlayerScreen();

	}
	
}







