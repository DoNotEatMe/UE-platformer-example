// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagePop.h"
#include "Kismet/GameplayStatics.h"
#include "WG/WGCharacter.h"
#include "Components/TextBlock.h"

void UDamagePop::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(),0);
	AWGCharacter* Player = Cast<AWGCharacter>(Controller);
	if (Player)
	{
		//Player->OnHealthUpdated.AddDynamic(this,&UDamagePop::DamagePop);
		
	}
}

void UDamagePop::DamagePop(float DamageAmount)
{
	Damage->SetText(FText::AsNumber(DamageAmount));
}
