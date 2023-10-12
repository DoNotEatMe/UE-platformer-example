// Copyright Epic Games, Inc. All Rights Reserved.

#include "WGCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "gameHUD.h"
#include "TrapBase.h"
#include "Trap_Explosive_comp.h"
#include "trap_platform.h"
#include "WGGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"


//////////////////////////////////////////////////////////////////////////
// AWGCharacter

AWGCharacter::AWGCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;

	Health = MaxHealth;


}

void AWGCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// TODO: Transfer to gameMode
	if(PlayerHUDClass)
	{
		APlayerController* FPC = UGameplayStatics::GetPlayerController(GetWorld(),0);
		check(FPC);
		PlayerHUD = CreateWidget<UgameHUD>(FPC, PlayerHUDClass);
		check(PlayerHUD);
		PlayerHUD->AddToPlayerScreen();

		//PlayerHUD->OnHealthUpdated.AddDynamic(this,)		
	}


	//Old
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),Atrap_platform::StaticClass(),Actors);
	for (AActor* Actor : Actors)
	{
		Atrap_platform* Trap = Cast<Atrap_platform>(Actor);
		if (Trap && Trap->ActorHasTag("Explode"))
		{
			Trap->OnApplyDamage.AddDynamic(this, &AWGCharacter::ApplyDamage);
		}
	}

	// Refactored
	TArray<AActor*> TrapActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATrapBase::StaticClass(),TrapActors);
	for (AActor* Actor : TrapActors)
	{
		ATrapBase* TrapBase = Cast<ATrapBase>(Actor);
		if (TrapBase)
		{
			UTrap_Explosive_comp* Trap = Cast<UTrap_Explosive_comp>(TrapBase->GetComponentByClass(UTrap_Explosive_comp::StaticClass()));
			if (Trap)
			{
				Trap->OnApplyDamage.AddDynamic(this, &AWGCharacter::ApplyDamage);
			}
			else
			{
				UE_LOG(LogTemp,Error,TEXT("Cannot get Trap to OnApplyDamage.AddDynamic in Character"));
			}
			
		}
	}
	
}

void AWGCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	Super::EndPlay(EndPlayReason);
	
}


float AWGCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AWGCharacter::ApplyDamage(float DamageAmount, AActor* Trap, FDamageEvent& DamageEvent)
{

	//DamageEvent DamageEvent; 	
	if (Health > 0 ){
		float ActualDamage = TakeDamage(DamageAmount, DamageEvent, this->GetController(), Trap);
		Health -= ActualDamage;
		if (Health <= 0)
		{
			AWGGameMode* GameMode = Cast<AWGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			if(GameMode)
			{
				UE_LOG(LogTemp,Warning,TEXT("Dead and GameMode ok"));
				OnGameOver.Broadcast(false);
			}
		}
		OnHealthUpdated.Broadcast(Health,MaxHealth);

	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWGCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWGCharacter::Look);

	}

}

void AWGCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWGCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}






