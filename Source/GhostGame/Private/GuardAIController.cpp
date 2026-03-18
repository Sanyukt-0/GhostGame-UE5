// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardAIController.h"
#include "GuardCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/Actor.h"

void AGuardAIController::BeginPlay()
{
	Super::BeginPlay();

	CurrentPatrolIndex = 0;
	SetState(EGuardState::Patrol);
	AGuardCharacter* Guard = Cast<AGuardCharacter>(GetPawn());


	if (Guard && Guard->PatrolPoints.Num() > 0) {
		MoveToActor(Guard->PatrolPoints[CurrentPatrolIndex]);
	}
}

void AGuardAIController::SetState(EGuardState NewState)
{
	CurrentState = NewState;
}


void AGuardAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AGuardCharacter* Guard = Cast<AGuardCharacter>(GetPawn());

	if (CurrentState == EGuardState::Patrol) {

		if (Guard && Guard->PatrolPoints.Num() > 0) {
			
			float Distance = FVector::Dist(GetPawn()->GetActorLocation(), Guard->PatrolPoints[CurrentPatrolIndex]->GetActorLocation());
			
			if (Distance < 100.f) {
				CurrentPatrolIndex = (CurrentPatrolIndex + 1) % Guard->PatrolPoints.Num();
				MoveToActor(Guard->PatrolPoints[CurrentPatrolIndex]);
			}
		}
		
	}
	else if (CurrentState == EGuardState::Alert)
	{

		if (Player && Guard) 
		{
			MoveToActor(Player);
			if (FVector::Dist(Player->GetActorLocation(), Guard->GetActorLocation()) > 1000.f)
			{
				StopMovement();
				SetState(EGuardState::Investigate);
			}
		}
	}

	
}
