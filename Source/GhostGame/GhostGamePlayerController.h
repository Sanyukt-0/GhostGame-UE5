// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "GhostGamePlayerController.generated.h"


class UInputMappingContext;
class UInputAction;


/**
 *  Player controller for a top-down perspective game.
 *  Implements point and click based controls
 */
UCLASS(abstract)
class AGhostGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	/** Initialize input bindings */
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* CrouchAction;
	
	void Move(const FInputActionValue& Value);
	void StartCrouch();
	void EndCrouch();


public:

	/** Constructor */
	AGhostGamePlayerController();

};


