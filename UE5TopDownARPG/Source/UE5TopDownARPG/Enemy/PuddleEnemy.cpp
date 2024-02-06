// Fill out your copyright notice in the Description page of Project Settings.


#include "PuddleEnemy.h"
#include "../UE5TopDownARPG.h"
#include "../BattleArenaGameInstance.h"
#include "../UE5TopDownARPGPlayerController.h"

void APuddleEnemy::Death() 
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Death of an Enemy"));

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector Location = GetActorLocation();
	//to make the spawned actor lay on the ground
	Location.Z -= 98;
	FRotator Rotation = GetActorRotation();
	AActor* SpawnedActor = GetWorld()->SpawnActor(AfterDeathSpawnClass, &Location, &Rotation, SpawnParameters);
	
	//live several seconds after spawned
	if (IsValid(SpawnedActor))
	{
		SpawnedActor->SetLifeSpan(Duration);
	}
	UBattleArenaGameInstance* GameInstance = Cast<UBattleArenaGameInstance>(GetGameInstance());
	if (IsValid(GameInstance))
	{
		GameInstance->SetAliveEnemies(GameInstance->GetAliveEnemies() - 1);
		if (GameInstance->GetAllWavesSpawned() && GameInstance->GetAliveEnemies() == 0) {
			AUE5TopDownARPGPlayerController* PlayerController = Cast<AUE5TopDownARPGPlayerController>(GetWorld()->GetFirstPlayerController());

			if (PlayerController)
			{
				PlayerController->OnPlayerKilledAllEnemies();
			}

		}
	}
	GetWorld()->GetTimerManager().ClearTimer(DeathHandle);

	Destroy();
}