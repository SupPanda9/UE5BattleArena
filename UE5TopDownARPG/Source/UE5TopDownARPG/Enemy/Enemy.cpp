// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Abilities/BaseAbility.h"
#include "../UE5TopDownARPG.h"
#include "GameFramework/Actor.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	OnTakeAnyDamage.AddDynamic(this, &AEnemy::TakeAnyDamage);
}

void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (AbilityTemplate != nullptr)
	{
		AbilityInstance = NewObject<UBaseAbility>(this, AbilityTemplate);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool AEnemy::ActivateAbility(FVector Location)
{
	if (IsValid(AbilityInstance))
	{
		return AbilityInstance->Activate(Location);
	}
	return false;
}

void AEnemy::TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	Health -= Damage;
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Health %f"), Health);

	if (Health <= 0.0f)
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		if (TimerManager.IsTimerActive(DeathHandle) == false)
		{
			GetWorld()->GetTimerManager().SetTimer(DeathHandle, this, &AEnemy::Death, DeathDelay);
		}
	}
}

void AEnemy::Death()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Death of an Enemy"));


	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector Location = GetActorLocation();
	//to make the spawned actor lay on the ground

	FRotator Rotation = GetActorRotation();
	if (FMath::RandBool())
	{
		AActor* SpawnedActor = GetWorld()->SpawnActor(AfterDeathSpawnClass, &Location, &Rotation, SpawnParameters);
		//live several seconds after spawned
		if (SpawnedActor)
		{
			SpawnedActor->SetLifeSpan(Duration);
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(DeathHandle);

	Destroy();
}
