// Copyright Epic Games, Inc. All Rights Reserved.

#include "GhostGamePlayerController.h"
#include "GameFramework/Pawn.h"
#include "GhostGameCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GhostGame.h"

AGhostGamePlayerController::AGhostGamePlayerController()
{
	

	// configure the controller
	bShowMouseCursor = false;
	
}

void AGhostGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Only set up input on local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			// Setup mouse input events
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGhostGamePlayerController::Move);
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AGhostGamePlayerController::StartCrouch);
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AGhostGamePlayerController::EndCrouch);



		}
		else
		{
			UE_LOG(LogGhostGame, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}

}

void AGhostGamePlayerController::Move(const FInputActionValue & Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	APawn* ControlPawn = GetPawn();

	const FVector ForwardDirection = FVector::ForwardVector;
	const FVector RightDirection = FVector::RightVector;

	if (ControlPawn) {
		ControlPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlPawn->AddMovementInput(RightDirection, MovementVector.X);
	}

}

void AGhostGamePlayerController::StartCrouch()
{

}

void AGhostGamePlayerController::EndCrouch()
{

}