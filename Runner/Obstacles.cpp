// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles.h"
#include "Components/BoxComponent.h"
#include "PlayerRunnerCharacter.h"

// Sets default values
AObstacles::AObstacles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	rock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock"));
	rock->SetupAttachment(RootComponent);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(rock);

}

// Called when the game starts or when spawned
void AObstacles::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this,&AObstacles::OnOverlapBegin);
}

// Called every frame
void AObstacles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!GetOwner()) 
	{
		Destroy();
	}

}

// Check if player is overlaped with the obstacle.
void AObstacles::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerRunnerCharacter* player = Cast<APlayerRunnerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	AActor* PlayerActor = Cast<AActor>(player);
	if(PlayerActor == OtherActor && OtherActor != this)
	{
		player->FinishGame();
	}
}

