#include "GameOver.h"
#include "WG/Traps/TrapBase.h"
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

		TArray<AActor*> TrapBases;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATrapBase::StaticClass(),TrapBases);
		for (AActor* Traps: TrapBases)
		{
			ATrapBase* Trap = Cast<ATrapBase>(Traps);
			if (Trap)
			{
				Trap->ResetTimers();
			}
		}
		UGameplayStatics::OpenLevel(GetWorld(), "ThirdPersonMap", false);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("RestartLevel() in GameOver.cpp error finding playercontroller/gamemode "));
	}
}

void UGameOver::PlaygroundStart()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;
		PlayerController->SetInputMode(FInputModeGameOnly());

		TArray<AActor*> TrapBases;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATrapBase::StaticClass(),TrapBases);
		for (AActor* Traps: TrapBases)
		{
			ATrapBase* Trap = Cast<ATrapBase>(Traps);
			if (Trap)
			{
				Trap->ResetTimers();
			}
		}
		UGameplayStatics::OpenLevel(GetWorld(), "TrapPlayground", false);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("PlaygroundStart() in GameOver.cpp error finding playercontroller/gamemode "));
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
