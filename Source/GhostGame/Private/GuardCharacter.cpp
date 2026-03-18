// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardCharacter.h"
#include "GuardAIController.h"
#include "Perception/PawnSensingComponent.h"
#include "GhostGameCharacter.h"

// Sets default values
AGuardCharacter::AGuardCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AGuardAIController::StaticClass();

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing"));
	PawnSensingComponent->SightRadius = 1000.f;
	PawnSensingComponent->SetPeripheralVisionAngle(60.f);
}

void AGuardCharacter::OnPawnSeen(APawn* SeenPawn)
{
    //UE_LOG(LogTemp, Warning, TEXT("PAWN SEEN"));

    if (!SeenPawn)
    {
        //UE_LOG(LogTemp, Warning, TEXT("SeenPawn is NULL"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("SeenPawn class: %s"), *SeenPawn->GetClass()->GetName());

    AGhostGameCharacter* Player = Cast<AGhostGameCharacter>(SeenPawn);
    AGuardAIController* AI = Cast<AGuardAIController>(GetController());

    if (Player && AI)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Player confirmed! Switching to Alert"));
        AI->SetState(EGuardState::Alert);
    }
    else
    {
        /*UE_LOG(LogTemp, Warning, TEXT("Cast failed - Player: %s, AI: %s"),
            Player ? TEXT("valid") : TEXT("null"),
            AI ? TEXT("valid") : TEXT("null"));*/
    }
}

// Called when the game starts or when spawned
void AGuardCharacter::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Guard BeginPlay called"));
	if (PawnSensingComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PawnSensing component found"));
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AGuardCharacter::OnPawnSeen);
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("PawnSensing component is NULL"));
	}
}

// Called every frame
void AGuardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGuardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    

}

