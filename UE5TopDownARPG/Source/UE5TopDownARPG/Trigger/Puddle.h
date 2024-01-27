// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrigger.h"
#include "Puddle.generated.h"


UCLASS()
class APuddle : public ABaseTrigger
{
	GENERATED_BODY()
	
	virtual void ActionStart(AActor* ActorInRange) override;

private:
	UPROPERTY()
	AActor* Target;

	FTimerHandle CustomDamageTickTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;
};
