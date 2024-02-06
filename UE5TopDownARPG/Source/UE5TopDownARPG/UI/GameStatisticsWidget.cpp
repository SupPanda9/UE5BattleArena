// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStatisticsWidget.h"
#include "../BattleArenaGameInstance.h"

void UGameStatisticsWidget::SetValues()
{
	UBattleArenaGameInstance* GameInstance = Cast<UBattleArenaGameInstance>(GetGameInstance());
	AliveEnemies = FString::FromInt(GameInstance->GetAliveEnemies());
	KilledEnemies = FString::FromInt(GameInstance->GetKilledEnemies());
	CurrentWaveNumber = FString::FromInt(GameInstance->GetCurrentWaveNumber());
}
