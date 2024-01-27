// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "PuddleEnemy.generated.h"

/**
 * 
 */
UCLASS()
class APuddleEnemy : public AEnemy
{
	GENERATED_BODY()
public:

private:
	virtual void Death() override;
};
