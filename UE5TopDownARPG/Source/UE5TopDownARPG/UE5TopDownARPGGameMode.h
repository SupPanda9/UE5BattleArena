// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE5TopDownARPGGameMode.generated.h"

UCLASS(minimalapi)
class AUE5TopDownARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE5TopDownARPGGameMode();

	virtual void BeginPlay() override;
	void EndGame(bool IsWin);
	void SpawnWave();
	//void SpawnEnemy(TArray<int> RandomIndex, FActorSpawnParameters SpawnParams, FVector SpawnLocation, TArray<TSubclassOf<AActor>> EnemyClasses);

public:
	// Declare the enemy blueprint classes as UPROPERTY variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PuddleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> MeleeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> RangedClass;

	FTimerHandle WaveSpawnTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	int MaxPuddle = 2;
	
	UPROPERTY(EditDefaultsOnly)
	int MaxMelee = 2;

	UPROPERTY(EditDefaultsOnly)
	int MaxRanged = 1;
	
	UPROPERTY(EditDefaultsOnly)
	int NumberOfWaves = 1;

	UPROPERTY(EditDefaultsOnly)
	int CurrentWave = 1;

	UPROPERTY(EditDefaultsOnly)
	int TimeBetweenWaves = 15.0f; //seconds between waves spawn

	UPROPERTY(EditDefaultsOnly)
	int InitialDelay = 5.0f; //seconds before the first wave

};
