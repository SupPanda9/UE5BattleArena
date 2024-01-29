// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "UObject/Object.h"
#include "Components/BoxComponent.h"
#include "PunchAbility.generated.h"


/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UPunchAbility : public UBaseAbility
{
	GENERATED_BODY()
	
public:
	virtual bool Activate(FVector Location) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* PunchMontage;

	/*UFUNCTION()
	void OnPunchEnded(UAnimMontage* Montage, bool bInterrupted);*/

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;
};
