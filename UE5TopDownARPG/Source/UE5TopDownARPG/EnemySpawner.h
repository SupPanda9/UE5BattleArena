// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy/Enemy.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UEnemySpawner : public UObject
{
	GENERATED_BODY()
public:
	UEnemySpawner();

protected:
	void ActionStart();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> MeleeClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> RangedClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> PuddleClass;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* SpawnLocationComponent;

	UPROPERTY(EditDefaultsOnly)
	int NumberOfWaves = 1;

	UPROPERTY(EditDefaultsOnly)
	int NumberOfActorsToSpawn = 1;

	UPROPERTY(EditDefaultsOnly)
	float InitialDelay;

	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenWaves = 1.0f;

	FTimerHandle WaveSpawnTimerHandle;
private:
	void SpawnWave();

	int CurrentWave;
};
