// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BattleArenaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UBattleArenaGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	void OnPropertyChanged();
	void SetDefaults();

	FORCEINLINE void SetNumberOfWaves(int NewNumber) { NumberOfWaves = NewNumber; };
	FORCEINLINE int GetNumberOfWaves() { return NumberOfWaves; };

	FORCEINLINE void SetIsInfinite(bool isChecked) { bIsInfinite = isChecked;};
	FORCEINLINE int GetIsInfinite() { return bIsInfinite; };

	FORCEINLINE void SetAllWavesSpawned(bool AllSpawned) { bAllWavesSpawned = AllSpawned; };
	FORCEINLINE int GetAllWavesSpawned() { return bAllWavesSpawned; };

	FORCEINLINE void SetAliveEnemies(int NumberOfEnemies) { AliveEnemies = NumberOfEnemies; OnPropertyChanged(); };
	FORCEINLINE int GetAliveEnemies() { return AliveEnemies; };
	
	FORCEINLINE void SetKilledEnemies(int NumberOfEnemies) { KilledEnemies = NumberOfEnemies; OnPropertyChanged();};
	FORCEINLINE int GetKilledEnemies() { return KilledEnemies; };

	FORCEINLINE void SetCurrentWaveNumber(int CurrentWave) { CurrentWaveNumber = CurrentWave; OnPropertyChanged();};
	FORCEINLINE int GetCurrentWaveNumber() { return CurrentWaveNumber; };
private:
	UPROPERTY()
	int NumberOfWaves = 1;

	UPROPERTY()
	bool bIsInfinite = 0;

	UPROPERTY()
	bool bAllWavesSpawned = 0;

	UPROPERTY()
	int AliveEnemies = 0;

	UPROPERTY()
	int KilledEnemies = 0;

	UPROPERTY()
	int CurrentWaveNumber = 0;
};
