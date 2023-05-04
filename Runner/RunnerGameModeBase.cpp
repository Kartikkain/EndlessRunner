// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameModeBase.h"
#include "FloorTile.h"
#include "Engine/World.h"
#include "PlayerRunnerCharacter.h"
#include "TimerManager.h"


void ARunnerGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    Player = Cast<APlayerRunnerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

    HandleGameStart();
  


}

void ARunnerGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Setting the game start value to true after T time.
void ARunnerGameModeBase::HandleGameStart()
{
    if(!Player) return;
    StartGame();
    FTimerHandle GameStartTimerHandle;
    FTimerDelegate GameStartDelegate  = FTimerDelegate::CreateUObject(Player,&APlayerRunnerCharacter::ChangeGameState,true);
    GetWorldTimerManager().SetTimer(GameStartTimerHandle,GameStartDelegate,GameStartDelay,false);
}

// Getting the time value from player and consverting to MM : SS format and return the fstring. 
FString ARunnerGameModeBase::GetTime() const
{   
   TCHAR* PrefixZero = TEXT("0");
   FString PrefixZeroString = FString(PrefixZero);

   if(!Player) return PrefixZeroString;

   float TimeTillGameOver = Player->GetGameTime();
   
   TCHAR* TimeSeprator = TEXT(" : ");
   FString TimeSepratorString = FString(TimeSeprator);  
   

   int32 minutes = TimeTillGameOver/60;
   FString minuteString = FString::FromInt(minutes);
   if(minutes < 10) minuteString = PrefixZeroString + minuteString;

   int32 TimeInInt = TimeTillGameOver;
   int32 seconds = TimeInInt % 60;
   FString secondsString = FString::FromInt(seconds);

   if(seconds < 10) secondsString = PrefixZeroString + secondsString;

   FString TimeString = minuteString + TimeSepratorString + secondsString;

   return TimeString;
}

//Getting the Distance From player and converting that distance into meter and return it.

FString ARunnerGameModeBase::GetDistance() const
{
    TCHAR* Unit = TEXT(" M");
    FString UnitString = FString(Unit);

    if(!Player) return UnitString;

    int32 pDistance = Player->GetPlayerDistance();
    FString pDistanceString = FString::FromInt(pDistance) + UnitString;

    return pDistanceString;
    
}
