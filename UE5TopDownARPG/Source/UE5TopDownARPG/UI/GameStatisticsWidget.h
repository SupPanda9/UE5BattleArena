// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStatisticsWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UGameStatisticsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetValues();
	
	// The text variables will be bound to the text block widgets
	UPROPERTY(BlueprintReadWrite)
	FString AliveEnemies;

	UPROPERTY(BlueprintReadWrite)
	FString KilledEnemies;

	UPROPERTY(BlueprintReadWrite)
	FString CurrentWaveNumber;
};
