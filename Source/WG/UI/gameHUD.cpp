#include "gameHUD.h"
#include "WG/WGCharacter.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

void UgameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
	AWGCharacter* Player = Cast<AWGCharacter>(Controller);
	if (Player)
	{
		Player->OnHealthUpdated.AddDynamic(this,&UgameHUD::HandleHealthUpdate);
		
	}
	
}

void UgameHUD::HandleHealthUpdate(float UpdHealth,float UpdMaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(UpdHealth/UpdMaxHealth);
	}
}


