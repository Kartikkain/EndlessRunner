// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportPowerUp.h"
#include "Components/BoxComponent.h"
#include "PlayerRunnerCharacter.h"

// Sets default values
ATeleportPowerUp::ATeleportPowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Power Up Mesh"));
	PowerUpMesh->SetupAttachment(RootComponent);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box->SetupAttachment(PowerUpMesh);

}

// Called when the game starts or when spawned
void ATeleportPowerUp::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this,&ATeleportPowerUp::OnOverlapBegin);
	
}

// Called every frame
void ATeleportPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!GetOwner()) Destroy();

}

// Check if player is overlaped with the Teleport powerUp.
void ATeleportPowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerRunnerCharacter* player = Cast<APlayerRunnerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	AActor* PlayerActor = Cast<AActor>(player);
	if(PlayerActor == OtherActor && OtherActor != this)
	{
		player->TeleportPower();	
		Destroy();
	}

}
