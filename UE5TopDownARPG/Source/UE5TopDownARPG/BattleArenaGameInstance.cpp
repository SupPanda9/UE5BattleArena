// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleArenaGameInstance.h"
#include "UE5TopDownARPGHUD.h"

void UBattleArenaGameInstance::OnPropertyChanged()
{

    AHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD();
    AUE5TopDownARPGHUD*  MyHUD= Cast<AUE5TopDownARPGHUD>(HUD);

    // If the cast is successful, call the UpdateScore function of the HUD class
    if (MyHUD)
    {
        MyHUD->UpdateGameStatistics();
    }
}

void UBattleArenaGameInstance::SetDefaults()
{
    NumberOfWaves = 1;

    bIsInfinite = 0;

    bAllWavesSpawned = 0;

    AliveEnemies = 0;

    KilledEnemies = 0;

    CurrentWaveNumber = 0;

}
