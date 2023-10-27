// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	//Check distance between AI pawn and target actor
	UBlackboardComponent* BlackBordComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBordComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackBordComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float distance = FVector::Distance(TargetActor->GetActorLocation(),AIPawn->GetActorLocation());
					bool bWithinRange = distance < 1000.0f;
					bool bHasLoss = false;
					if (bWithinRange) {
						bHasLoss = MyController->LineOfSightTo(TargetActor);
					}
					
					BlackBordComp->SetValueAsBool(AttackRangeKey.SelectedKeyName , (bWithinRange&&bHasLoss));
				}
			}
		}
	}
}
