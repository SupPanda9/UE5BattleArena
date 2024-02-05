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

	FORCEINLINE void SetNumberOfWaves(int NewNumber) { NumberOfWaves = NewNumber; };
	FORCEINLINE int GetNumberOfWaves() { return NumberOfWaves; };
private:
	UPROPERTY()
	int NumberOfWaves = 1;

};
