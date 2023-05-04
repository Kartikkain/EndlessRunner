// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Obstacles.h"
#include "SpeedPowerUp.h"
#include "TeleportPowerUp.h"
// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	Floor->SetupAttachment(Scene);

}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();

	AttachPoint = FindComponentByClass<UArrowComponent>();
	GenerateObstacles();
	
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Generate Obstacles and powerups Randomly.
void AFloorTile::GenerateObstacles()
{
	int32 RandomLane = FMath::RandRange(0,ObsticlePositions.Num()-1);
	FVector Location = ObsticlePositions[RandomLane];
	FRotator Rotation = Floor->GetComponentRotation();
	int32 PRandomLane = FMath::RandRange(0,PowerUpPositions.Num()-1);
	FVector PLocation = PowerUpPositions[PRandomLane];
	AObstacles* RockObstacle = GetWorld()->SpawnActor<AObstacles>(ObstacleClass,Location,Rotation);
	RockObstacle->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
	RockObstacle->SetOwner(this);
	
	int32 SpawnOptions = FMath::RandRange(0,2);
	ASpeedPowerUp* SpeedPU;
	ATeleportPowerUp* TeleportPU;
	if(SpawnOptions == 0)
	{
		SpeedPU = GetWorld()->SpawnActor<ASpeedPowerUp>(SpeedPowerUpClass,PLocation,Rotation);
		SpeedPU->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
		SpeedPU->SetOwner(this);
	}
	else if(SpawnOptions == 1)
	{
		TeleportPU = GetWorld()->SpawnActor<ATeleportPowerUp>(TeleportPowerUpClass,PLocation,Rotation);
		TeleportPU->AttachToActor(this,FAttachmentTransformRules::KeepRelativeTransform);
		TeleportPU->SetOwner(this);
	}
	
	
}


