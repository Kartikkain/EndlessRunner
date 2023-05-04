// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerRunnerCharacter.generated.h"

UCLASS()
class RUNNER_API APlayerRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerRunnerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	bool HasGameStarted = false;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SpeedUpPower();
	void TeleportPower();
	void ChangeGameState(bool Gamestate);
	float GetGameTime();
	int32 GetPlayerDistance();
	void FinishGame();

private:

	float TimeTillGameOver;
	int32 CurrentLane = 1;
	APlayerController* CharacterController = nullptr;
	bool IsSwipe = false;
	FVector2D StartVector = FVector2D::ZeroVector;
	FVector2D EndVector = FVector2D::ZeroVector;
	FVector ChangeLocation;
	FVector PlayerStartLocation;

	UPROPERTY(VisibleAnywhere)
	float playerSpeed;

	UPROPERTY(EditDefaultsOnly)
	float PlayTime = 180;

	UPROPERTY(EditDefaultsOnly)
	int32 SpeedUp = 2;

	UPROPERTY(EditDefaultsOnly)
	int32 TeleportDistance = 100;

	UPROPERTY(EditDefaultsOnly)
	float RunSpeedMagnitude = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	TArray<float> LanePositions;

	void Move(float DeltaTime);
	void CheckForSwipe();
	void DetermineTypeOfSwipe();
	FVector2D GetTouchVector();
	FVector MoveSideways(int32 LaneShift);
	void ResetSpeed();
	void RestartCurrentLevel();

};
