// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunnerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API ARunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintPure)
	FString GetTime() const;

	UFUNCTION(BlueprintPure)
	FString GetDistance() const;

private:

	FVector NextAttachPointLocation;
	class APlayerRunnerCharacter* Player = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFloorTile> FloorClass;

	UPROPERTY(EditDefaultsOnly)
	float GameStartDelay = 4.0f;

	void HandleGameStart();
	
};
