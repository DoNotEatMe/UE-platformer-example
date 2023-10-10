// Fill out your copyright notice in the Description page of Project Settings.


#include "gameHUD.h"

#include "Components/ProgressBar.h"

void UgameHUD::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth/MaxHealth);
	}
}

