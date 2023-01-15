// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower():FireRange(300.f), FireRate(2.f) {}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if(Tank){
        if(inFireRange()) {
            RotateTurret(Tank->GetActorLocation());
        }
    }
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
    Destroy();
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle,this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if(!Tank) {
        return;
    }

    if(Tank->bAlive && inFireRange()) {
        Fire();
    }
}

bool ATower::inFireRange()
{
    if(!Tank) {
        return false;
    }

    // Find the distance to the Tank
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

    return (Distance <= FireRange);
}

