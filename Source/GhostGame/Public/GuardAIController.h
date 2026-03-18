// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "GuardAIController.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGuardState : uint8
{
	Patrol,
	Alert,
	Investigate
};



UCLASS()
class GHOSTGAME_API AGuardAIController : public AAIController
{
	GENERATED_BODY()

public:
	EGuardState CurrentState;
	FVector LastKnownPosition;


	void SetState(EGuardState NewState);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	int32 CurrentPatrolIndex;

	
};
