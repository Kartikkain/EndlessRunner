// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

UCLASS()
class RUNNER_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Floor;

	UPROPERTY(EditDefaultsOnly)
	TArray<FVector> ObsticlePositions;

	UPROPERTY(EditDefaultsOnly)
	TArray<FVector> PowerUpPositions;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AObstacles> ObstacleClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASpeedPowerUp> SpeedPowerUpClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ATeleportPowerUp> TeleportPowerUpClass;

	class UArrowComponent* AttachPoint;

	

	void GenerateObstacles();

};
