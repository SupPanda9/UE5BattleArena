// Fill out your copyright notice in the Description page of Project Settings.


#include "Puddle.h"
#include "Engine/DamageEvents.h"

void APuddle::ActionStart(AActor* ActorInRange)
{
	Target = ActorInRange;

	if(IsValid(Target))
	{
		ActorInRange->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
	}

	Destroy();
}


