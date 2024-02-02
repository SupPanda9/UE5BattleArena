// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../UE5TopDownARPG.h"
#include "../Enemy/Enemy.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AProjectile::OnBeginOverlap);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
}

void AProjectile::SetOwnerTeam(FString Team)
{
	OwnerTeam = Team;
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLocation = GetActorLocation();
	float DistanceTraveled = FVector::Distance(InitialLocation, CurrentLocation);
	
	//Destroy the projectile if it travels more than its range
	if (DistanceTraveled > Distance)
	{
		Destroy();
	}
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* Enemy = Cast<AEnemy>(Other);
	FString OtherTeam;
	if (Enemy != nullptr)
	{
		OtherTeam = Enemy->GetTeam();
	}
	else
	{
		AUE5TopDownARPGCharacter* Player = Cast<AUE5TopDownARPGCharacter>(Other);
		if (Player != nullptr)
		{
			OtherTeam = Player->GetTeam();
		}
		else
		{
			UE_LOG(LogUE5TopDownARPG, Log, TEXT("Other is not an enemy or a player"));
			return;
		}
	}
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Owner is %s, Other is %s"), *OwnerTeam, *OtherTeam);
	if (!OwnerTeam.IsEmpty() && IsValid(Other) && OwnerTeam != OtherTeam)
	{
		Other->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
		Destroy();
	}
}
