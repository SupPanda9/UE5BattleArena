// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TransformToPuddle.h"
#include "../Enemy/Enemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_TransformToPuddle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
	if (IsValid(AIController) == false)
	{
		return EBTNodeResult::Failed;
	}

	AEnemy* PossesedCharacter = Cast<AEnemy>(AIController->GetPawn());
	if (IsValid(PossesedCharacter) == false)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (IsValid(BlackboardComponent) == false)
	{
		return EBTNodeResult::Failed;
	}

	PossesedCharacter->Kill();

	return EBTNodeResult::Failed;
}