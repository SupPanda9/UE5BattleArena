// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UE5TopDownARPG.h"
#include "Enemy/Enemy.h"
#include "BattleArenaGameInstance.h"


AUE5TopDownARPGGameMode::AUE5TopDownARPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUE5TopDownARPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AUE5TopDownARPGGameMode::SpawnWave()
{
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    TArray<TSubclassOf<AActor>> EnemyClasses;
    EnemyClasses.Add(MeleeClass);
	EnemyClasses.Add(PuddleClass);
    EnemyClasses.Add(RangedClass);

	TArray<int> RandomIndex;
	for (int i = 0; i < MaxMelee; i++)
	{
		RandomIndex.Add(0);
	}
	for (int i = 0; i < MaxPuddle; i++)
	{
		RandomIndex.Add(1);
	}
	for (int i = 0; i < MaxRanged; i++)
	{
		RandomIndex.Add(2);
	}

	UBattleArenaGameInstance* GameInstance = Cast<UBattleArenaGameInstance>(GetGameInstance());

    for (int i = 0; i < MaxMelee + MaxPuddle + MaxRanged; i++) {
        FVector SpawnLocation;
        SpawnLocation.X = FMath::RandRange(300.0f, 3200.0f);
        SpawnLocation.Y = FMath::RandRange(300.0f, 3200.0f);
        SpawnLocation.Z = 100.0f;

        TSubclassOf<AEnemy> EnemyClass = EnemyClasses[RandomIndex[i]];
        UE_LOG(LogUE5TopDownARPG, Log, TEXT("%s"), EnemyClass);
        if (IsValid(EnemyClass))
        {
            GetWorld()->SpawnActor<AActor>(EnemyClass, SpawnLocation, FRotator(), SpawnParameters);
			GameInstance->SetAliveEnemies(GameInstance->GetAliveEnemies() + 1);
        }
    }

	if (CurrentWave == NumberOfWaves) 
	{
		GameInstance->SetAllWavesSpawned(true);
		GetWorld()->GetTimerManager().ClearTimer(WaveSpawnTimerHandle);
		return;
	}

	CurrentWave++;
}

void AUE5TopDownARPGGameMode::BeginPlay()
{
	UBattleArenaGameInstance* GameInstance = Cast<UBattleArenaGameInstance>(GetGameInstance());
	if (GameInstance->GetIsInfinite()) {
		NumberOfWaves = -1;
	}
	else {
		NumberOfWaves = GameInstance->GetNumberOfWaves();
	}
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Number Of Waves %d"), NumberOfWaves);
	GetWorld()->GetTimerManager().SetTimer(WaveSpawnTimerHandle, this, &AUE5TopDownARPGGameMode::SpawnWave, TimeBetweenWaves, true, InitialDelay);
}

void AUE5TopDownARPGGameMode::EndGame(bool IsWin)
{
	if (IsWin)
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Win"));
	}
	else
	{
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Lose"));
	}
}

