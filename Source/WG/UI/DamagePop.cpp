// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagePop.h"

#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "WG/WGCharacter.h"

void UDamagePop::NativeConstruct()
{
	Super::NativeConstruct();

}

void UDamagePop::DamagePop(float DamageAmount, APlayerController* PlayerController, UWidgetComponent* WidgetComponent)
{
	UE_LOG(LogTemp,Warning,TEXT("%f"), DamageAmount);
	FVector2D ScreenPosition;
	PlayerController->ProjectWorldLocationToScreen(WidgetComponent->GetComponentLocation(),ScreenPosition);
	this->SetPositionInViewport(ScreenPosition);
	
	Damage->SetText(FText(FText::Format(FText::FromString("{0}"),FText::AsNumber(DamageAmount))));
	this->AddToViewport();
	this->PlayAnimation(FloatUpAnimation,0,1,EUMGSequencePlayMode::Forward,1,false);
}

void UDamagePop::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
	if (Animation == FloatUpAnimation)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}










