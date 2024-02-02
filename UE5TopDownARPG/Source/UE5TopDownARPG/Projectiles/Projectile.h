// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	void SetOwnerTeam(FString Team);
	void Tick(float DeltaTime);
	void BeginPlay();

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float Distance = 200.0f;

	FVector InitialLocation;

	UPROPERTY()
	FString OwnerTeam = FString(TEXT(""));
};
