// Fill out your copyright notice in the Description page of Project Settings.


#include "BoltAbility.h"
#include "../Projectiles/Projectile.h"
#include "../Animations/UE5TopDownARPGAnimInstance.h"
#include "GameFramework/Character.h"
#include "../Enemy/Enemy.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../UE5TopDownARPG.h"
#include "Kismet/GameplayStatics.h"

bool UBoltAbility::Activate(FVector Location)
{
  if (Super::Activate(Location) == false)
  {
    return false;
  }

	ServerRPC_SpawnProjectile(Location);

	return true;
}

void UBoltAbility::ServerRPC_SpawnProjectile_Implementation(FVector Location)
{
	ACharacter* Owner = Cast<ACharacter>(GetOuter());
	if (IsValid(Owner) == false)
	{
		return;
	}

	USkeletalMeshComponent* MeshComponent = Owner->GetMesh();
	if (IsValid(MeshComponent))
	{
		UUE5TopDownARPGAnimInstance* AnimInstance = Cast<UUE5TopDownARPGAnimInstance>(MeshComponent->GetAnimInstance());
		if (IsValid(AnimInstance))
		{
			AnimInstance->SetIsAttacking();
		}
	}

	FVector Direction = Location - Owner->GetActorLocation();
	Direction.Z = 0.0f;
	Direction.Normalize();

	FVector ProjectileSpawnLocation = Owner->GetActorLocation() + Direction * 100.0f;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AEnemy* EnemyOwner = Cast<AEnemy>(Owner);
	FString OwnerTeam;
	if (EnemyOwner != nullptr)
	{
		OwnerTeam = EnemyOwner->GetTeam();
		UE_LOG(LogUE5TopDownARPG, Log, TEXT("Owner is an enemy BOLTABILITY"));
	}
	else
	{
		AUE5TopDownARPGCharacter* PlayerOwner = Cast<AUE5TopDownARPGCharacter>(Owner);
		if (PlayerOwner != nullptr)
		{
			OwnerTeam = PlayerOwner->GetTeam();
		}
		else
		{
			UE_LOG(LogUE5TopDownARPG, Log, TEXT("Owner is not an enemy nor a player"));
			return;
		}
	}

	/*AProjectile* Projectile = Cast<AProjectile>(GetWorld()->SpawnActor<AActor>(ProjectileClass, ProjectileSpawnLocation, Direction.Rotation(), SpawnParameters));
	Projectile->SetOwnerTeam(OwnerTeam);
	if (IsValid(Projectile) == false)
	{
		return;
	}*/

	FTransform SpawnTransform(Direction.Rotation(), ProjectileSpawnLocation);
	AProjectile* Projectile = Cast<AProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileClass, SpawnTransform));
	if (IsValid(Projectile))
	{
		Projectile->SetOwnerTeam(OwnerTeam);
		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	}

	return;
}
