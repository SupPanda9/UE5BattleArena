// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGAIController.h"
#include "../Enemy/Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"

AUE5TopDownARPGAIController::AUE5TopDownARPGAIController()
{
  /*AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));*/
  BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
  BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AUE5TopDownARPGAIController::OnPossess(APawn* InPawn)
{
  Super::OnPossess(InPawn);

  AEnemy* PossesedCharacter = Cast<AEnemy>(InPawn);
  if (IsValid(PossesedCharacter))
  {
    UBehaviorTree* Tree = PossesedCharacter->GetBehaviorTree();
    if (IsValid(Tree))
    {
      BlackboardComponent->InitializeBlackboard(*Tree->GetBlackboardAsset());
      BehaviorTreeComponent->StartTree(*Tree);
    }
  }
}

void AUE5TopDownARPGAIController::OnUnPossess()
{
  Super::OnUnPossess();

  BehaviorTreeComponent->StopTree();
}