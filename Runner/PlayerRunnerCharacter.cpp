// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRunnerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


// Sets default values
APlayerRunnerCharacter::APlayerRunnerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerRunnerCharacter::BeginPlay()
{
	Super::BeginPlay();
	TimeTillGameOver = PlayTime;
	playerSpeed = RunSpeedMagnitude;
	CharacterController = UGameplayStatics::GetPlayerController(this,0);
	ChangeLocation = GetActorLocation();
	PlayerStartLocation = GetActorLocation();
}

// Called every frame
void APlayerRunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(HasGameStarted)
	{
		TimeTillGameOver -= DeltaTime;
		if(TimeTillGameOver < 0) FinishGame();

		
		FVector CurrentLocation = GetActorLocation();

		if(CurrentLocation.Y != ChangeLocation.Y )
		{
			float InterpolateY = FMath::Lerp(CurrentLocation.Y,ChangeLocation.Y,0.7);
			FVector InterpolationLocation(GetActorLocation().X,InterpolateY,GetActorLocation().Z);
			SetActorLocation(InterpolationLocation);
		}
		Move(DeltaTime);
	}

}

// Called to bind functionality to input
void APlayerRunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Finger1"),IE_Pressed,this,&APlayerRunnerCharacter::CheckForSwipe);
	PlayerInputComponent->BindAction(TEXT("Finger1"),IE_Released,this,&APlayerRunnerCharacter::DetermineTypeOfSwipe);

}


// Moving The Character Forward.
void APlayerRunnerCharacter::Move(float DeltaTime)
{
	AddMovementInput(GetActorForwardVector() * DeltaTime * playerSpeed);
}

// Check if the gesture is swipe or just a tab.
void APlayerRunnerCharacter::CheckForSwipe()
{
	StartVector = GetTouchVector();
	FVector2D TempVector = GetTouchVector();
	FVector2D VectorDifference = StartVector - TempVector;
	float VectorLength; 
	FVector2D Direction;
	VectorDifference.ToDirectionAndLength(Direction,VectorLength);
	if(VectorLength < 100) IsSwipe = true;
}

// Determine What kind of swipe like up, right or left.
void APlayerRunnerCharacter::DetermineTypeOfSwipe()
{
	if(!IsSwipe) return;

	EndVector = GetTouchVector();
	FVector2D StartToEndDiffrence = StartVector - EndVector;
	float Xabs = FMath::Abs(StartToEndDiffrence.X);
	float Yabs = FMath::Abs(StartToEndDiffrence.Y);
	if(Xabs > Yabs && StartToEndDiffrence.X > 0.0f)
	{
		ChangeLocation = MoveSideways(-1);
	}
	else if(Xabs > Yabs && StartToEndDiffrence.X < 0.0f)
	{
		ChangeLocation = MoveSideways(1);
	}
	else if(StartToEndDiffrence.Y > 0.0)
	{
		Jump();
	}
}

// Get location of a touch on screen.
FVector2D APlayerRunnerCharacter::GetTouchVector()
{
	if(!CharacterController) return FVector2D::ZeroVector;

	float ScreenLocationX;
	float ScreenLocationY;
	bool IsCurrentlyPressed;
	CharacterController->GetInputTouchState(ETouchIndex::Touch1,ScreenLocationX,ScreenLocationY,IsCurrentlyPressed);
	return FVector2D(ScreenLocationX,ScreenLocationY);
}

// Get player Y Location on swipe. 
FVector APlayerRunnerCharacter::MoveSideways(int32 LaneShift)
{
	CurrentLane += LaneShift;
	CurrentLane  = FMath::Clamp(CurrentLane,0,2);
	FVector StartLocation = GetActorLocation();
	FVector NewLocation(GetActorLocation().X,LanePositions[CurrentLane],GetActorLocation().Z);
	return NewLocation;
}

// Increase the speed by some percentage and set back to normal after T seconds.
void APlayerRunnerCharacter::SpeedUpPower()
{
	if(playerSpeed == RunSpeedMagnitude * SpeedUp) return;
	playerSpeed *= SpeedUp;
	playerSpeed = FMath::Clamp(playerSpeed,RunSpeedMagnitude,RunSpeedMagnitude * SpeedUp);
	UE_LOG(LogTemp,Warning,TEXT("Speed: %f"),playerSpeed);
	FTimerHandle ResetSpeedHandle;
	GetWorldTimerManager().SetTimer(ResetSpeedHandle,this,&APlayerRunnerCharacter::ResetSpeed,5,false);

}

void APlayerRunnerCharacter::ResetSpeed()
{
	playerSpeed /= SpeedUp;
	playerSpeed = FMath::Clamp(playerSpeed,RunSpeedMagnitude,RunSpeedMagnitude * SpeedUp);
	UE_LOG(LogTemp,Warning,TEXT("Speed: %f"),playerSpeed);

}

// Move player to D distance.
void APlayerRunnerCharacter::TeleportPower()
{
	FVector PlayerCurrentLocation = GetActorLocation();
	FVector PlayerNewLocation = PlayerCurrentLocation + GetActorForwardVector() * TeleportDistance;
	SetActorLocation(PlayerNewLocation);
	UE_LOG(LogTemp,Warning,TEXT("TELEPORT"));
}

// Change if the game has started or ended.
void APlayerRunnerCharacter::ChangeGameState(bool Gamestate)
{
	HasGameStarted = Gamestate;
}

// Get Timer Value
float APlayerRunnerCharacter::GetGameTime()
{
	return TimeTillGameOver;
}

// Get player distace from start location.
int32 APlayerRunnerCharacter::GetPlayerDistance()
{
	FVector playerCurrentLocation = GetActorLocation();
	int32 playerDistance = FMath::Abs((playerCurrentLocation.X - PlayerStartLocation.X)/100);
	return playerDistance;
}

// Disable mesh and tick.
void APlayerRunnerCharacter::FinishGame()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	HasGameStarted = false;
	FTimerHandle LevelRestartTimerHandle;
	GetWorldTimerManager().SetTimer(LevelRestartTimerHandle,this,&APlayerRunnerCharacter::RestartCurrentLevel,5,false);
}

//Restart the level.
void APlayerRunnerCharacter::RestartCurrentLevel()
{
	APlayerController* RunnerController = GetWorld()->GetFirstPlayerController();
	if(RunnerController) RunnerController->RestartLevel();
}
