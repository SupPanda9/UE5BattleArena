// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"


// Fill out your copyright notice in the Description page of Project Settings.

UEnemySpawner::UEnemySpawner()
{
	SpawnLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocationComponent"));
}

void UEnemySpawner::ActionStart()
{
	CurrentWave = 1;

	GetWorld()->GetTimerManager().SetTimer(WaveSpawnTimerHandle, this, &UEnemySpawner::SpawnWave, TimeBetweenWaves, true, InitialDelay);
}

void UEnemySpawner::SpawnWave()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int i = 0; i < NumberOfActorsToSpawn; i++)
	{
		GetWorld()->SpawnActor<AActor>(MeleeClass, SpawnLocationComponent->GetComponentLocation(), FRotator(), SpawnParameters);
		GetWorld()->SpawnActor<AActor>(PuddleClass, SpawnLocationComponent->GetComponentLocation(), FRotator(), SpawnParameters);
		GetWorld()->SpawnActor<AActor>(RangedClass, SpawnLocationComponent->GetComponentLocation(), FRotator(), SpawnParameters);
	}

	if (CurrentWave == NumberOfWaves)
	{
		GetWorld()->GetTimerManager().ClearTimer(WaveSpawnTimerHandle);
		return;
	}

	CurrentWave++;
}