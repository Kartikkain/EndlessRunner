// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPowerUp.h"
#include "Components/BoxComponent.h"
#include "PlayerRunnerCharacter.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ASpeedPowerUp::ASpeedPowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpeedPowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Speed Power Up Mesh"));
	SpeedPowerUpMesh->SetupAttachment(RootComponent);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box->SetupAttachment(SpeedPowerUpMesh);

}

// Called when the game starts or when spawned
void ASpeedPowerUp::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this,&ASpeedPowerUp::OnOverlapBegin);
}

// Called every frame
void ASpeedPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!GetOwner()) Destroy();
}

// Check if player is overlaped with the Speed Power Up.
void ASpeedPowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerRunnerCharacter* player = Cast<APlayerRunnerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	AActor* PlayerActor = Cast<AActor>(player);
	if(PlayerActor == OtherActor && OtherActor != this)
	{
		player->SpeedUpPower();
		Destroy();
	}

}


