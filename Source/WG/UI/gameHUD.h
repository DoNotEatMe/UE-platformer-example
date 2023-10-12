#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "gameHUD.generated.h"

UCLASS()
class WG_API UgameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UProgressBar* HealthBar;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void HandleHealthUpdate(float UpdHealth,float UpdMaxHealth);

};
